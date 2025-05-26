#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include "graphicUnit.h"
#include "graphicSettings.h"

using namespace std;
class GraphicManager {
    public:
        vector<GLfloat> vertices;
        vector<GLuint> indices;
        vector<GraphicUnit*> graphicUnits;

        GraphicManager();
        ~GraphicManager();

        /***
         * @brief Adds a GraphicUnit to the manager
         * 
         * @param unit The pointer to the GraphicUnit to be added
         * @details The function adds the unit to the graphicUnits vector and updates the vertices and indices vectors accordingly.
         */
        void addUnit(GraphicUnit* unit);

        /*** 
         * @brief Removes a GraphicUnit from the graphicUnits vector and updates the vertices and indices vectors accordingly.
         * 
         * @param index The index of the GraphicUnit to be removed.
         * @details Removes vertices and indices associated with the indexed GraphicUnit from the vectors and updates the indices of the remaining GraphicUnits.
         */
        void removeUnit(int index);
};