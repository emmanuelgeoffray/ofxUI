/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#ifndef OFXUI_ROTARY_SLIDER_POINTING_DIRECTION
#define OFXUI_ROTARY_SLIDER_POINTING_DIRECTION

#include "ofxUIRotarySlider.h"

class ofxUIRotarySliderPointingDirection : public ofxUIRotarySlider
{
public:    
    ofxUIRotarySliderPointingDirection(float x, float y, float w, float _min, float _max, float _value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUIRotarySlider(x, y, w, _min, _max, _value, name, _size)
    {
    }
    
    ofxUIRotarySliderPointingDirection(float w, float _min, float _max, float _value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUIRotarySlider(w, _min, _max, _value, _name, _size)
    {
    }
    
    ofxUIRotarySliderPointingDirection(float x, float y, float w, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUIRotarySlider(x, y, w, _min, _max, value, name, _size)
    {
    }
    
    ofxUIRotarySliderPointingDirection(float w, float _min, float _max, float *_value, string _name, int _size = OFX_UI_FONT_SMALL) : ofxUIRotarySlider(w, _min, _max, _value, _name, _size)
    {
    }    
    
    ~ofxUIRotarySliderPointingDirection()
    {
    }
    
    virtual void drawFill()    
    {
        if(draw_fill)
        {			
            ofFill(); 
            ofSetColor(color_fill); 
            drawArcStripPointing(value); 
        }
    }

    virtual void drawFillHighlight()
    {
        if(draw_fill_highlight)
        {
            ofFill(); 
            ofSetColor(color_fill_highlight); 
            drawArcStripPointing(value); 
        }        
    }   
    
    void drawArcStripPointing(float percent)
    {
        float theta = ofMap(percent, 0, 1, 0, 360.0, true); 
        float theta1 = theta -10;
        float theta2 = theta +10;

        
        ofPushMatrix(); 
        ofTranslate(rect->getX(),rect->getY()); 

        ofBeginShape(); 

        {
            float x = sin(-ofDegToRad(theta1)); 
            float y = cos(-ofDegToRad(theta1));         
            ofVertex(center.x+outerRadius*x,center.y+outerRadius*y); 
        }
        
        for(int i = theta1; i <= theta2; i+=10)
        {
            float x = sin(-ofDegToRad(i)); 
            float y = cos(-ofDegToRad(i)); 
            
            ofVertex(center.x+outerRadius*x,center.y+outerRadius*y); 
        }
        
        {
            float x = sin(-ofDegToRad(theta2)); 
            float y = cos(-ofDegToRad(theta2));         
            ofVertex(center.x+outerRadius*x,center.y+outerRadius*y); 
            ofVertex(center.x+innerRadius*x,center.y+innerRadius*y); 
        }
        
        for(int i = theta2; i >= theta1; i-=10)
        {
            float x = sin(-ofDegToRad(i)); 
            float y = cos(-ofDegToRad(i)); 
            
            ofVertex(center.x+innerRadius*x,center.y+innerRadius*y); 
        }
        
        {
            float x = sin(-ofDegToRad(theta1)); 
            float y = cos(-ofDegToRad(theta1));         
            ofVertex(center.x+innerRadius*x,center.y+innerRadius*y); 
        }
                
        ofEndShape(); 
        ofPopMatrix();         
    }
      
protected:    //inherited: ofxUIRectangle *rect; ofxUIWidget *parent; 
    
}; 

#endif
