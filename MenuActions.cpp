#include <string>
#include <include/AppendModes.h>
#include <imgui/imgui.h>
#include <include/Matrix2.h>

class Storage;
void appendTransformation(Storage & s, Matrix2D & transformation);
std::string to_string(ClickModes & mode)
{
    if (mode == AddPoint)
        return "AddPoint";
    if (mode == MovePoint)
        return "MovePoint";
    if (mode == RemovePoint)
        return "RemovePoint";
    if (mode == MoveOrigin)
        return "MoveOrigin";
    if (mode == TransformationTranslate)
        return "TransformationTranslate";
    if (mode == RotateTransformation)
        return "RotateTransformation";
    return "Undefined";
}

void flipX(Storage & s)
{
    Matrix2D matrix;

    matrix.value[0][0] = -1;
    matrix.value[0][1] = 0;
    matrix.value[1][0] = 0;
    matrix.value[1][1] = 1;

    appendTransformation(s, matrix);
}

void flipY(Storage & s)
{
    Matrix2D matrix;

    matrix.value[0][0] = 1;
    matrix.value[0][1] = 0;
    matrix.value[1][0] = 0;
    matrix.value[1][1] = -1;

    appendTransformation(s, matrix);
}

