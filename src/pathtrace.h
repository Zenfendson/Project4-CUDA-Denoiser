#pragma once

#include <vector>
#include "scene.h"

void InitDataContainer(GuiDataContainer* guiData);
void pathtraceInit(Scene *scene);
void pathtraceFree();
void pathtrace(uchar4* pbo, int frame, int iteration);
void showGBuffer(uchar4 *pbo);
void showImage(uchar4 *pbo, int iter);
void runDenoiser(float ui_filterSize, float ui_c_phi, float ui_n_phi, float ui_p_phi);
void showDenoisedImage(uchar4* pbo, int iter);

