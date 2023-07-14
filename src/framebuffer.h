#pragma once
#include <vector>
#include <fstream>
#include "color.h"
#include "vertex.h"

class FrameBuffer {
public:
    FrameBuffer(int width, int height)
        : width_(width), height_(height), pixels_(width * height) {}

    void setPixel(int x, int y, const Color& color) {
        if (x >= 0 && x < width_ && y >= 0 && y < height_) {
            pixels_[x + y * width_] = color;
        }
    }

    void clear(const Color& color) {
        for (auto& pixel : pixels_) {
            pixel = color;
        }
    }

    void renderBuffer(const std::string& filename) {
        // Crear archivo BMP
        std::ofstream file(filename, std::ios::binary);

        // Encabezado del archivo BMP
        const int fileSize = 54 + 3 * width_ * height_;
        const int dataOffset = 54;

        file << "BM";  // Tipo de archivo BMP
        file.write(reinterpret_cast<const char*>(&fileSize), 4);  // Tamaño total del archivo
        file.write("\x00\x00\x00\x00", 4);  // Reservado
        file.write(reinterpret_cast<const char*>(&dataOffset), 4);  // Offset de datos de la imagen
        file.write("\x28\x00\x00\x00", 4);  // Tamaño del encabezado de información del BMP
        file.write(reinterpret_cast<const char*>(&width_), 4);  // Ancho de la imagen
        file.write(reinterpret_cast<const char*>(&height_), 4);  // Alto de la imagen
        file.write("\x01\x00", 2);  // Planos de color (1)
        file.write("\x18\x00", 2);  // Bits por píxel (24)
        file.write("\x00\x00\x00\x00", 4);  // Compresión (ninguna)
        const int imageSize = 3 * width_ * height_;
        file.write(reinterpret_cast<const char*>(&imageSize), 4);  // Tamaño de la imagen en bytes
        file.write("\x00\x00\x00\x00", 4);  // Resolución horizontal (0)
        file.write("\x00\x00\x00\x00", 4);  // Resolución vertical (0)
        file.write("\x00\x00\x00\x00", 4);  // Colores en la paleta de color (0)
        file.write("\x00\x00\x00\x00", 4);  // Colores importantes (0)

        // Escribir datos de píxeles en el archivo BMP
        for (int y =  0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
                const Color& pixel = pixels_[x + y * width_];
                file.write(reinterpret_cast<const char*>(&pixel.b), 1);  // Componente azul
                file.write(reinterpret_cast<const char*>(&pixel.g), 1);  // Componente verde
                file.write(reinterpret_cast<const char*>(&pixel.r), 1);  // Componente rojo
            }
        }

        // Cerrar el archivo BMP
        file.close();
    }

    void drawLine(float x0, float y0, float x1, float y1, const Color& color) {
        int startX = static_cast<int>(x0);
        int startY = static_cast<int>(y0);
        int endX = static_cast<int>(x1);
        int endY = static_cast<int>(y1);

        // Verificar si los puntos iniciales o finales se salen del framebuffer
        if (startX < 0 || startX >= width_ || startY < 0 || startY >= height_ ||
            endX < 0 || endX >= width_ || endY < 0 || endY >= height_) {
            return;
        }

        int dx = abs(endX - startX);
        int dy = abs(endY - startY);
        int sx = (startX < endX) ? 1 : -1;
        int sy = (startY < endY) ? 1 : -1;
        int err = dx - dy;

        while (true) {
            setPixel(startX, startY, color);

            if (startX == endX && startY == endY) {
                break;
            }

            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                startX += sx;
            }
            if (e2 < dx) {
                err += dx;
                startY += sy;
            }
        }
    }

    void drawPolygon(const std::vector<Vertex2>& points, const Color& color) {
        int numPoints = static_cast<int>(points.size());

        for (int i = 0; i < numPoints - 1; ++i) {
            const Vertex2& currentPoint = points[i];
            const Vertex2& nextPoint = points[i + 1];
            if (isInsideFramebuffer(currentPoint) || isInsideFramebuffer(nextPoint)) {
                drawLine(currentPoint.x, currentPoint.y, nextPoint.x, nextPoint.y, color);
            }
        }

        // Conectar el último punto con el primer punto
        const Vertex2& lastPoint = points[numPoints - 1];
        const Vertex2& firstPoint = points[0];
        if (isInsideFramebuffer(lastPoint) || isInsideFramebuffer(firstPoint)) {
            drawLine(lastPoint.x, lastPoint.y, firstPoint.x, firstPoint.y, color);
        }
    }

    void fillPolygon(const std::vector<Vertex2>& vertices, const Color& color) {
        float minY = vertices[0].y;
        float maxY = vertices[0].y;
        for (const auto& vertex : vertices) {
            if (vertex.y < minY) {
                minY = vertex.y;
            }
            if (vertex.y > maxY) {
                maxY = vertex.y;
            }
        }

        for (int y = static_cast<int>(minY); y <= static_cast<int>(maxY); ++y) {
            std::vector<float> intersections;

            for (size_t i = 0; i < vertices.size(); ++i) {
                const Vertex2& currentVertex = vertices[i];
                const Vertex2& nextVertex = vertices[(i + 1) % vertices.size()];

                if ((currentVertex.y <= y && nextVertex.y > y) ||
                    (currentVertex.y > y && nextVertex.y <= y)) {
                    float x = currentVertex.x +
                              (y - currentVertex.y) *
                                  (nextVertex.x - currentVertex.x) /
                                  (nextVertex.y - currentVertex.y);
                    intersections.push_back(x);
                }
            }

            std::sort(intersections.begin(), intersections.end());

            for (size_t i = 0; i < intersections.size(); i += 2) {
                int startX = static_cast<int>(intersections[i]);
                int endX = static_cast<int>(intersections[i + 1]);

                if (startX < 0) {
                    startX = 0;
                }
                if (endX >= width_) {
                    endX = width_ - 1;
                }

                for (int x = startX; x <= endX; ++x) {
                    setPixel(x, y, color);
                }
            }
        }
    }

private:
    int width_;
    int height_;
    std::vector<Color> pixels_;

    bool isInsideFramebuffer(const Vertex2& point) {
        return (point.x >= 0 && point.x < width_ &&
                point.y >= 0 && point.y < height_);
    }
};
