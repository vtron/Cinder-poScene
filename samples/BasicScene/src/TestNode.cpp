//
//  TestNode.cpp
//  BasicScene
//
//  Created by Stephen Varga on 3/18/14.
//
//
#include "cinder/Timeline.h"

#include "TestNode.h"

const int TestNode::NUM_ROWS		= 3;
const int TestNode::NUM_COLS		= 5;
const int TestNode::SIZE			= 70;
const int TestNode::SPACING         = 20;

TestNodeRef TestNode::create() {
    return TestNodeRef(new TestNode());
}

TestNode::TestNode()
{
    setInteractionEnabled(true);
}

void TestNode::setup()
{
    setDrawBoundsEnabled(true);
    setPosition(50,50);
    
    for(int i=0; i<NUM_ROWS; i++) {
		for(int j=0; j<NUM_COLS; j++) {
            po::ShapeRef r = po::Shape::createRect(SIZE);
            r->setInteractionEnabled(true);
            
            //Set Position in grid
			float xPos = j * (SIZE + SPACING);
			float yPos = i * (SIZE + SPACING);
			r->setPosition(xPos, yPos);
            
            addEvent(po::MouseEvent::Type::DOWN_INSIDE, r);
            addChild(r);
        }
    }
}

void TestNode::draw() {
    ci::gl::color(ci::Color(255,0,0));
    ci::gl::drawSolidRect(ci::Rectf(0,0, 50,50));
}

void TestNode::squareFinishedTweening(po::ShapeRef square) {
    square->fillColor.set(255,255,255);
}

//Events
void TestNode::mouseDown(po::MouseEvent event)
{
}

void TestNode::mouseMove(po::MouseEvent event)
{
}

void TestNode::mouseDownInside(po::MouseEvent event)
{
    po::ShapeRef thisRect = std::static_pointer_cast<po::Shape>(event.source);
    
    if(!thisRect->rotationAnim.isComplete()) {
        thisRect->setRotation(thisRect->getRotation());
        squareFinishedTweening(thisRect);
    } else {
        thisRect->fillColor.set(255,0,0);
        
        if (thisRect->getRotation() == 360.f) {
            thisRect->rotationAnim = 0.f;
        }
        
        ci::app::timeline().apply(&thisRect->rotationAnim, 360.f, 4.0f)
                            .finishFn(std::bind( &TestNode::squareFinishedTweening,this, thisRect));
    }
    
}

void TestNode::mouseMoveInside(po::MouseEvent event)
{
}

void TestNode::mouseUpInside(po::MouseEvent event)
{
}

void TestNode::mouseUp(po::MouseEvent event)
{
    //std::cout << "Test node Mouse Up event!" << std::endl;
    //rect->fillColor.set(255,255,255);
}