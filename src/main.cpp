#include "vertex.h"
#include "color.h"
#include "framebuffer.h"
#include <vector>
#include <fstream>

// Tamaño del framebuffer
const int FRAMEBUFFER_WIDTH = 800;
const int FRAMEBUFFER_HEIGHT = 600;

// Variables globales
FrameBuffer framebuffer(FRAMEBUFFER_WIDTH, FRAMEBUFFER_HEIGHT);
Color clearColor;

void clear() {
    framebuffer.clear(clearColor);
}

void setCurrentColor(const Color& color) {
    clearColor = color;
}

void point(const Vertex2& vertex) {
    int x = static_cast<int>(vertex.x);
    int y = static_cast<int>(vertex.y);

    if (x >= 0 && x < FRAMEBUFFER_WIDTH && y >= 0 && y < FRAMEBUFFER_HEIGHT) {
        framebuffer.setPixel(x, y, clearColor);
    }
}

void poligon1() {
    // Crear un vector de puntos para el polígono #1
    std::vector<Vertex2> polygonPoints = {
        {165, 380}, {185, 360}, {180, 330}, {207, 345}, {233, 330}, {230, 360}, {250, 380}, {220, 385}, {205, 410}, {193, 383}
    };

    // Rellenar el polígono #1 en el framebuffer
    const Color fillColor(255, 255, 0);  // Amarillo
    framebuffer.fillPolygon(polygonPoints, fillColor);

    // Dibujar el polígono #1 en la framebuffer
    const Color outlineColor(255, 255, 255);  // Blanco
    for (size_t i = 0; i < polygonPoints.size() - 1; ++i) {
        const Vertex2& startPoint = polygonPoints[i];
        const Vertex2& endPoint = polygonPoints[i + 1];
        framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);
    }
    const Vertex2& startPoint = polygonPoints[polygonPoints.size() - 1];
    const Vertex2& endPoint = polygonPoints[0];
    framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);
}

void poligon2() {
    // Crear un vector de puntos para el polígono #2
    std::vector<Vertex2> polygonPoints = {
        {321, 335}, {288, 286}, {339, 251}, {374, 302}
    };

    // Rellenar el polígono #2 en el framebuffer
    const Color fillColor(0, 0, 255);  // Azul
    framebuffer.fillPolygon(polygonPoints, fillColor);

    // Dibujar el polígono #2 en la framebuffer
    const Color outlineColor(255, 255, 255);  // Blanco
    for (size_t i = 0; i < polygonPoints.size() - 1; ++i) {
        const Vertex2& startPoint = polygonPoints[i];
        const Vertex2& endPoint = polygonPoints[i + 1];
        framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);
    }
    const Vertex2& startPoint = polygonPoints[polygonPoints.size() - 1];
    const Vertex2& endPoint = polygonPoints[0];
    framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);
}

void poligon3() {
    // Crear un vector de puntos para el polígono #3
    std::vector<Vertex2> polygonPoints = {
        {377, 249}, {411, 197}, {436, 249}
    };

    // Rellenar el polígono #3 en el framebuffer
    const Color fillColor(255, 0, 0);  // Rojo
    framebuffer.fillPolygon(polygonPoints, fillColor);

    // Dibujar el polígono #3 en la framebuffer
    const Color outlineColor(255, 255, 255);  // Blanco
    for (size_t i = 0; i < polygonPoints.size() - 1; ++i) {
        const Vertex2& startPoint = polygonPoints[i];
        const Vertex2& endPoint = polygonPoints[i + 1];
        framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);
    }
    const Vertex2& startPoint = polygonPoints[polygonPoints.size() - 1];
    const Vertex2& endPoint = polygonPoints[0];
    framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);
}

void poligon4() {
    // Crear un vector de puntos para el polígono #4
    std::vector<Vertex2> polygonPoints = {
        {413, 177}, {448, 159}, {502, 88}, {553, 53}, {535, 36}, {676, 37}, {660, 52},
        {750, 145}, {761, 179}, {672, 192}, {659, 214}, {615, 214}, {632, 230}, {580, 230},
        {597, 215}, {552, 214}, {517, 144}, {466, 180}
    };

    // Rellenar el polígono #4 en el framebuffer
    const Color fillColor(0, 255, 0);  // Verde
    framebuffer.fillPolygon(polygonPoints, fillColor);

    // Dibujar el polígono #4 en la framebuffer
    const Color outlineColor(255, 255, 255);  // Blanco
    for (size_t i = 0; i < polygonPoints.size() - 1; ++i) {
        const Vertex2& startPoint = polygonPoints[i];
        const Vertex2& endPoint = polygonPoints[i + 1];
        framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);
    }
    const Vertex2& startPoint = polygonPoints[polygonPoints.size() - 1];
    const Vertex2& endPoint = polygonPoints[0];
    framebuffer.drawLine(startPoint.x, startPoint.y, endPoint.x, endPoint.y, outlineColor);
}

void poligon5() {
    // Crear un vector de puntos para el polígono #5
    std::vector<Vertex2> polygonPoints = {
        {682, 175}, {708, 120}, {735, 148}, {739, 170}
    };

    // Rellenar el polígono #5 en el framebuffer con color negro
    const Color fillColor(0, 0, 0);  // Negro
    framebuffer.fillPolygon(polygonPoints, fillColor);
}

void render() {
    // Limpiar el framebuffer
    clear();

    // Establecer el color de borrado (clear color)
    setCurrentColor(Color(0, 0, 128));  // Azul marino

    // Dibujar los polígonos
    poligon1();
    poligon2();
    poligon3();
    poligon4();
    poligon5();

    // Renderizar el framebuffer en un archivo BMP
    framebuffer.renderBuffer("out.bmp");
}

int main() {
    render();

    return 0;
}
