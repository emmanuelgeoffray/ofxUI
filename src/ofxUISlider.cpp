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

#include "ofxUISlider.h"
#include "ofxUI.h"

ofxUISlider::ofxUISlider() : ofxUIWidgetWithLabel()
{
    
}

ofxUISlider::ofxUISlider(string _name, float _min, float _max, float _value, float w, float h, float x, float y) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_value, w, h, x, y);
}

ofxUISlider::ofxUISlider(string _name, float _min, float _max, float *_value, float w, float h, float x, float y) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _value, w, h, x, y);
}

// DON'T USE THE NEXT CONSTRUCTORS
// This is maintained for backward compatibility and will be removed on future releases

ofxUISlider::ofxUISlider(float x, float y, float w, float h, float _min, float _max, float _value, string _name) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_value, w, h, x, y);
    //        ofLogWarning("OFXUISLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUISlider::ofxUISlider(float w, float h, float _min, float _max, float _value, string _name) : ofxUIWidgetWithLabel()
{
    useReference = false;
    init(_name, _min, _max, &_value, w, h, 0, 0);
    //        ofLogWarning("OFXUISLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUISlider::ofxUISlider(float x, float y, float w, float h, float _min, float _max, float *_value, string _name) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _value, w, h, x, y);
    //        ofLogWarning("OFXUISLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUISlider::ofxUISlider(float w, float h, float _min, float _max, float *_value, string _name) : ofxUIWidgetWithLabel()
{
    useReference = true;
    init(_name, _min, _max, _value, w, h, 0, 0);
    //        ofLogWarning("OFXUISLIDER: DON'T USE THIS CONSTRUCTOR. THIS WILL BE REMOVED ON FUTURE RELEASES.");
}

ofxUISlider::~ofxUISlider()
{
    if(!useReference)
    {
        delete valueRef;
    }
}

void ofxUISlider::init(string _name, float _min, float _max, float *_value, float w, float h, float x, float y)
{
    rect = new ofxUIRectangle(x,y,w,h);
    name = string(_name);
    if(w > h)
    {
        kind = OFX_UI_WIDGET_SLIDER_H;
    }
    else
    {
        kind = OFX_UI_WIDGET_SLIDER_V;
    }
    
    paddedRect = new ofxUIRectangle(-padding, -padding, w+padding*2.0, h+padding);
    paddedRect->setParent(rect);
    
    draw_fill = true;
    
    value = *_value;                                               //the widget's value
    if(useReference)
    {
        valueRef = _value;
    }
    else
    {
        valueRef = new float();
        *valueRef = value;
    }
    
    max = _max;
    min = _min;
    labelPrecision = 2;
    
    if(value > max)
    {
        value = max;
    }
    if(value < min)
    {
        value = min;
    }
    
    value = ofxUIMap(value, min, max, 0.0, 1.0, true);
    
    if(kind == OFX_UI_WIDGET_SLIDER_H)
    {
        label = new ofxUILabel(0,h+padding,string(name+" LABEL"), string(name + ": " + ofxUIToString(max,labelPrecision)), OFX_UI_FONT_SMALL);
    }
    else
    {
        label = new ofxUILabel(0,h+padding,string(name+" LABEL"), string(name), OFX_UI_FONT_SMALL);
    }
    
    label->setParent(label);
    label->setRectParent(rect);
    label->setEmbedded(true);
    increment = fabs(max - min) / 100.0;
    bRoundedToNearestInt = false;
    bClampValue = true;
}

bool ofxUISlider::getSetClampValue()
{
    return bClampValue;
}

void ofxUISlider::setClampValue(bool _bClampValue)
{
    bClampValue = _bClampValue;
}

void ofxUISlider::update()
{
    if(useReference)
    {
        value = ofxUIMap(*valueRef, min, max, 0.0, 1.0, bClampValue);
        updateLabel();
    }
}

void ofxUISlider::setDrawPadding(bool _draw_padded_rect)
{
    draw_padded_rect = _draw_padded_rect;
    label->setDrawPadding(false);
}

void ofxUISlider::setDrawPaddingOutline(bool _draw_padded_rect_outline)
{
    draw_padded_rect_outline = _draw_padded_rect_outline;
    label->setDrawPaddingOutline(false);
}

void ofxUISlider::drawBack()
{
    if(draw_back)
    {
        ofxUIFill();
        ofxUISetColor(color_back);
        rect->draw();
    }
}

void ofxUISlider::drawOutline()
{
    if(draw_outline)
    {
        ofNoFill();
        ofxUISetColor(color_outline);
        rect->draw();
    }
}

void ofxUISlider::drawOutlineHighlight()
{
    if(draw_outline_highlight)
    {
        ofNoFill();
        ofxUISetColor(color_outline_highlight);
        rect->draw();
    }
}

void ofxUISlider::drawFill()
{
    if(draw_fill && value > 0.0)
    {
        ofxUIFill();
        ofxUISetColor(color_fill);
        if(kind == OFX_UI_WIDGET_SLIDER_H)
        {
            ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*MIN(MAX(value, 0.0), 1.0), rect->getHeight());
        }
        else
        {
            ofxUIDrawRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*MIN(MAX(value, 0.0), 1.0));
        }
    }
}

void ofxUISlider::drawFillHighlight()
{
    if(draw_fill_highlight)
    {
        ofxUIFill();
        ofxUISetColor(color_fill_highlight);
        if(kind == OFX_UI_WIDGET_SLIDER_H)
        {
            ofxUIDrawRect(rect->getX(), rect->getY(), rect->getWidth()*MIN(MAX(value, 0.0), 1.0), rect->getHeight());
        }
        else
        {
            ofxUIDrawRect(rect->getX(), rect->getY()+rect->getHeight(), rect->getWidth(), -rect->getHeight()*MIN(MAX(value, 0.0), 1.0));
        }
        if(kind == OFX_UI_WIDGET_SLIDER_V)
        {
            label->drawString(rect->getX()+rect->getWidth()+padding, label->getRect()->getHeight()/2.0+rect->getY()+rect->getHeight()-rect->getHeight()*MIN(MAX(value, 0.0), 1.0), ofxUIToString(getScaledValue(),labelPrecision));
        }
    }
}

void ofxUISlider::mouseMoved(int x, int y )
{
    if(rect->inside(x, y))
    {
        state = OFX_UI_STATE_OVER;
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUISlider::mouseDragged(int x, int y, int button)
{
    if(hit)
    {
        state = OFX_UI_STATE_DOWN;
        input(x, y);
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUISlider::mousePressed(int x, int y, int button)
{
    if(rect->inside(x, y))
    {
        hit = true;
        state = OFX_UI_STATE_DOWN;
        input(x, y);
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
}

void ofxUISlider::mouseReleased(int x, int y, int button)
{
    if(hit)
    {
#ifdef TARGET_OPENGLES
        state = OFX_UI_STATE_NORMAL;
#else
        state = OFX_UI_STATE_OVER;
#endif
        input(x, y);
        triggerEvent(this);
    }
    else
    {
        state = OFX_UI_STATE_NORMAL;
    }
    stateChange();
    hit = false;
}

void ofxUISlider::keyPressed(int key)
{
    if(state == OFX_UI_STATE_OVER || state == OFX_UI_STATE_DOWN)
    {
        switch (key)
        {
            case OF_KEY_RIGHT:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_UP:
                setValue(getScaledValue()+increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_LEFT:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_DOWN:
                setValue(getScaledValue()-increment);
                triggerEvent(this);
                break;
                
            case OF_KEY_SHIFT:
#if OF_VERSION_MINOR > 7
            case OF_KEY_LEFT_SHIFT:
            case OF_KEY_RIGHT_SHIFT:
#endif
                bRoundedToNearestInt = true;
                break;
            default:
                break;
        }
    }
}

void ofxUISlider::keyReleased(int key)
{
    bRoundedToNearestInt = false;
}

void ofxUISlider::windowResized(int w, int h)
{
    
}

float ofxUISlider::getIncrement()
{
    return increment;
}

void ofxUISlider::setIncrement(float _increment)
{
    increment = _increment;
}

void ofxUISlider::input(float x, float y)
{
    if(kind == OFX_UI_WIDGET_SLIDER_H)
    {
        value = rect->percentInside(x, y).x;
    }
    else
    {
        value = 1.0-rect->percentInside(x, y).y;
    }
    
    if(value > 1.0)
    {
        value = 1.0;
    }
    else if(value < 0.0)
    {
        value = 0.0;
    }
    
    updateValueRef();
    updateLabel();
}

void ofxUISlider::updateValueRef()
{
    (*valueRef) = bRoundedToNearestInt ? ceil(getScaledValue()) : getScaledValue();
}

void ofxUISlider::updateLabel()
{
    if(kind == OFX_UI_WIDGET_SLIDER_H)
    {
        label->setLabel(name + ": " + ofxUIToString(getScaledValue(),labelPrecision));
    }
}

void ofxUISlider::stateChange()
{
    switch (state) {
        case OFX_UI_STATE_NORMAL:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
        case OFX_UI_STATE_OVER:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = true;
            label->unfocus();
        }
            break;
        case OFX_UI_STATE_DOWN:
        {
            draw_fill_highlight = true;
            draw_outline_highlight = true;
            label->focus();
        }
            break;
        case OFX_UI_STATE_SUSTAINED:
        {
            draw_fill_highlight = false;
            draw_outline_highlight = false;
            label->unfocus();
        }
            break;
            
        default:
            break;
    }
}

void ofxUISlider::setValue(float _value)
{
    value = ofxUIMap(_value, min, max, 0.0, 1.0, bClampValue);
    updateValueRef();
    updateLabel();
}

float ofxUISlider::getValue()
{
    return value;
}

float ofxUISlider::getPercentValue()
{
    return value;
}

float ofxUISlider::getScaledValue()
{
    return ofxUIMap(value, 0.0, 1.0, min, max, bClampValue);
}

ofxUILabel *ofxUISlider::getLabel()
{
    return label;
}

void ofxUISlider::setLabelVisible(bool _labelVisible)
{
    label->setVisible(_labelVisible);
    paddedRect->height -= label->getPaddingRect()->height;
}

void ofxUISlider::setVisible(bool _visible)
{
    visible = _visible;
    label->setVisible(visible);
}

void ofxUISlider::setParent(ofxUIWidget *_parent)
{
    parent = _parent;
    label->getRect()->setY(rect->getHeight()+padding);
    paddedRect->height = rect->getHeight() + label->getPaddingRect()->height + padding;
    paddedRect->x = -padding;
    paddedRect->y = -padding;
    if(label->getPaddingRect()->width > paddedRect->width)
    {
        paddedRect->width = label->getPaddingRect()->width;
    }
    updateValueRef();
    updateLabel();
}

void ofxUISlider::setLabelPrecision(int _precision) {
    labelPrecision = _precision;
    updateValueRef();
    updateLabel();
}

void ofxUISlider::setMax(float _max, bool bKeepValueTheSame)
{
    setMaxAndMin(_max, min, bKeepValueTheSame);
}

float ofxUISlider::getMax()
{
    return max;
}

void ofxUISlider::setMin(float _min, bool bKeepValueTheSame)
{
    setMaxAndMin(max, _min, bKeepValueTheSame);
}

float ofxUISlider::getMin()
{
    return min;
}

ofxUIVec2f ofxUISlider::getMaxAndMin()
{
    return ofxUIVec2f(max, min);
}

void ofxUISlider::setMaxAndMin(float _max, float _min, bool bKeepValueTheSame)
{
    max = _max;
    min = _min;
    
    if(!bKeepValueTheSame)
    {
        value = ofxUIMap(value, 0, 1.0, min, max, bClampValue);
        value = ofxUIMap(value, min, max, 0.0, 1.0, bClampValue);
        updateValueRef();
        updateLabel();
    }
}

bool ofxUISlider::isDraggable()
{
    return true;
}