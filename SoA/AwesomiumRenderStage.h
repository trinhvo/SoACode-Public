/// 
///  AwesomiumRenderStage.h
///  Seed of Andromeda
///
///  Created by Benjamin Arnold on 1 Nov 2014
///  Copyright 2014 Regrowth Studios
///  All Rights Reserved
///  
///  This file provides the render stage for awesomium UI
///

#pragma once

#ifndef AwesomiumRenderStage_h__
#define AwesomiumRenderStage_h__

#include <Vorb/graphics/IRenderStage.h>
#include <Vorb/graphics/GLProgram.h>

class IAwesomiumInterface;

class AwesomiumRenderStage : public vg::IRenderStage {
public:
    /// Constructor which injects dependencies
    /// @param awesomiumInterface: The user interface handle
    /// @param glProgram: The opengl program used to render the interface
    AwesomiumRenderStage(IAwesomiumInterface* awesomiumInterface);

    // Draws the render stage
    virtual void render() override;
private:
    IAwesomiumInterface* m_awesomiumInterface; ///< The user interface handle
};

#endif // AwesomiumRenderStage_h__