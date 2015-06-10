#include "poShape.h"

#include "Masking.h"
#include "poScene.h"
#include "Resources.h"

bool bUseFbo = false;
bool bShowMask = true;

using namespace po::scene;

MaskingRef Masking::create() {
    MaskingRef node(new Masking());
    node->setup();
    return node;
}


void Masking::setup() {
    //setPosition(200,50);
    
    ci::gl::TextureRef texture = ci::gl::Texture::create(ci::loadImage(ci::app::loadAsset(("fish.png"))));
    mZach = Shape::create(texture);
    //mZach->setTexture(texture, po::TextureFit::Type::EXACT);
//    mZach->setAlignment(po::Alignment::CENTER_CENTER);
    mZach->setPosition(ci::app::getWindowWidth()/2 - mZach->getHeight()/2, 0);
    //mZach->setAlignment(po::Alignment::CENTER_CENTER);
    
    targetPos = ci::app::getWindowHeight()/2 - mZach->getHeight()/2;
    //image->setRotation(45);
    addChild(mZach);
    
    //Create mask
    ci::gl::TextureRef maskTex = ci::gl::Texture::create(loadImage(ci::app::loadAsset("mask.png")));
    mMask = Shape::create(maskTex);
    //mZach->setMask(mMask);
    //mZach->setCacheToFboEnabled(true, 200,200);
    
    mMask->setFillColor(ci::Color(1,0,1));
    //mMask->setPosition(0,mZach->getHeight());
    //addChild(mMask);
    
    ci::app::getWindow()->connectKeyDown(&Masking::keyDown, this);
    
    //addChild(mMask);
    
    //Load the shader
//    try {
////        mShader = gl::GlslProg ( loadAsset("poMask_vert.glsl"), loadAsset( "poMask_frag.glsl"));
//        mShader = gl::GlslProg ( loadResource(RES_GLSL_PO_MASK_VERT), loadResource( RES_GLSL_PO_MASK_FRAG));
//    } catch (gl::GlslProgCompileExc e) {
//        console() << "Could not load shader: " << e.what() << std::endl;
//        exit(1);
//    }
    
    //ci::app::timeline().apply(&mZach->getRotationAnim(), 360.f, 3.f).loop();
    
    //setCacheToFboEnabled(true);
    
    //    po::ShapeRef mask = po::Shape::createRect(200,200);
    //    mask->setFillColor(255,0,255);
    //    mask->setAlignment(po::Alignment::CENTER_CENTER);
    //    mask->setPosition(image->getPosition().x, image->getPosition().y);
    ////    addChild(mask);

//    ci::app::timeline().apply(&mZach->getPositionAnim(), ci::Vec2f(ci::app::getWindowWidth()/2 - mZach->getHeight()/2, targetPos), 1.f);
//    ci::app::timeline().apply(&mMask->getPositionAnim(), ci::Vec2f(0, 0), 1.f);
}

void Masking::update()
{

}

//void Masking::_drawTree() {
//    if(!bUseFbo) {
//        po::Node::drawTree();
//        return;
//    }
//
//    {
//        //Save the window buffer
//        gl::SaveFramebufferBinding binding;
//        
//        //Setup the FBO
//        mFbo = gl::Fbo(getWidth(), getHeight());
//        gl::setViewport(mFbo.getBounds());
//        mFbo.bindFramebuffer();
//        
//        ci::CameraOrtho cam;
////        cam.setOrtho( 0,getBounds().getWidth(), getBounds().getHeight(), 0, -1, 1 );
//        cam.setOrtho( 0, getBounds().getWidth(), 0, getBounds().getHeight(), -1, 1 );
//        gl::setMatrices(cam);
//        
//        //Draw into the FBO
//        gl::pushMatrices();
//        gl::translate(-getFrame().getUpperLeft());
//        
//        ci::gl::clear(ci::Color(0,0,0));
//        po::Node::drawTree();
//        
//        gl::popMatrices();
//    }
//
//    gl::setViewport(app::getWindowBounds());
//    gl::setMatrices(getScene()->getCamera());
//    
//    _drawFbo();
//    
//}


void Masking::mouseMove(MouseEvent &event)
{
    maskPos = event.getLocalPos() - mMask->getTexture()->getSize()/2;
    //std::cout << event.getPos() << std::endl;
    //maskPos = event.getPos() - ci::Vec2f(mMaskTex->getWidth(), mMaskTex->getHeight())/2;
    //std::cout << maskPos << std::endl;
}


void Masking::keyDown(ci::app::KeyEvent &event)
{
    if(event.getChar() == 'm') {
        if(mZach->hasMask()) {
            mZach->removeMask();
        } else {
            mZach->setMask(mMask);
        }
    }
    
    else if(event.getChar() == 'f') {
        bUseFbo = !bUseFbo;
    }
}