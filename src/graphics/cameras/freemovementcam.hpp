/*
 * freemovementcam.hpp
 *
 *  Created on: Jun 18, 2012
 *      Author: zeheron
 */

#ifndef FREEMOVEMENTCAM_HPP_
#define FREEMOVEMENTCAM_HPP_

#include "core/definitions.hpp"
#include "graphics/camera.hpp"

class FreeMovementCam : public Camera
{
public:
    FreeMovementCam();
    virtual ~FreeMovementCam();

    virtual void handleinput(InputEvent& inputEvent) override;
};

#endif /* FREEMOVEMENTCAM_HPP_ */
