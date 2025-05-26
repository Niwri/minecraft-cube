#include "graphicManager.h"
#include <iostream>

using namespace std;

GraphicManager::GraphicManager() {
    this->vertices.reserve(1000);
    this->indices.reserve(1000);
}

GraphicManager::~GraphicManager() {
    for (GraphicUnit* unit : this->graphicUnits) {
        delete unit;
    }
        this->vertices.erase(this->vertices.begin(), this->vertices.end());
        this->indices.erase(this->indices.begin(), this->indices.end());
}

void GraphicManager::addUnit(GraphicUnit* unit) {
    if (unit == nullptr) {
        cout << "GraphicManager Error: Null unit" << endl;
        return;
    }
    
    this->graphicUnits.push_back(unit);
    
    unit->verticesIndex = this->vertices.size() / STRIDE;

    this->vertices.insert(vertices.end(), unit->vertices.begin(), unit->vertices.end());

    for (uint8_t i = 0; i < unit->indices.size(); i++) 
        unit->indices[i] += unit->verticesIndex;
    
    this->indices.insert(this->indices.end(), unit->indices.begin(), unit->indices.end());

}

void GraphicManager::removeUnit(int index) {
    if (index < 0 || index >= this->graphicUnits.size()) {
        cout << "GraphicManager Error: Invalid index" << endl;
        return;
    }

    GraphicUnit* unit = this->graphicUnits[index];

    int verticesLength = unit->vertices.size();
    int indicesLength = unit->indices.size();

    vertices.erase(vertices.begin() + unit->verticesIndex, vertices.begin() + unit->verticesIndex + unit->vertices.size());
    indices.erase(indices.begin() + unit->indicesIndex, indices.begin() + unit->indicesIndex + unit->indices.size());

    this->graphicUnits.erase(graphicUnits.begin() + index);

    for(size_t i = index; i < this->graphicUnits.size(); i++) {
        GraphicUnit* unit = this->graphicUnits[i];
        unit->verticesIndex -= verticesLength;
        unit->indicesIndex -= indicesLength;
    }
}