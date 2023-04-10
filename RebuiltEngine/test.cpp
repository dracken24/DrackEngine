#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

int main()
{
    // Initialisation de l'orientation de l'objet
    glm::quat orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));

    std::cout << "Orientation start : " << glm::to_string(orientation) << std::endl;

    orientation = glm::quat(glm::vec3(0.0f, 0.0f, glm::radians(90.0f)));

    // Affichage de l'orientation
    std::cout << "Orientation avant rotation : " << glm::to_string(orientation) << std::endl;

    // Rotation de l'objet autour de l'axe des Y
    orientation = glm::rotate(orientation, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

    // Affichage de l'orientation après rotation
    std::cout << "Orientation après rotation : " << glm::to_string(orientation) << std::endl;

    return 0;
}