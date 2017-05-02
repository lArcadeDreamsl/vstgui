//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework for VST plugins
//
// Version 4.3
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2015, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
//   * Redistributions of source code must retain the above copyright notice,
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this
//     software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#ifndef __iviewcreator__
#define __iviewcreator__

#include "../lib/vstguifwd.h"
#include <string>
#include <list>

namespace VSTGUI {
class IUIDescription;
class UIAttributes;

//-----------------------------------------------------------------------------
/// @brief View creator interface
///	@ingroup new_in_4_0
//-----------------------------------------------------------------------------
class IViewCreator
{
public:
	virtual ~IViewCreator () noexcept = default;
	
	enum AttrType {
		kUnknownType,
		kBooleanType,
		kIntegerType,
		kFloatType,
		kStringType,
		kColorType,
		kFontType,
		kBitmapType,
		kPointType,
		kRectType,
		kTagType,
		kListType,
		kGradientType
	};

	virtual IdStringPtr getViewName () const = 0;
	virtual IdStringPtr getBaseViewName () const = 0;
	virtual CView* create (const UIAttributes& attributes, const IUIDescription* description) const = 0;
	virtual bool apply (CView* view, const UIAttributes& attributes, const IUIDescription* description) const = 0;
	virtual bool getAttributeNames (std::list<std::string>& attributeNames) const = 0;
	virtual AttrType getAttributeType (const std::string& attributeName) const = 0;
	virtual bool getAttributeValue (CView* view, const std::string& attributeName, std::string& stringValue, const IUIDescription* desc) const = 0;
	// optional list type support
	virtual bool getPossibleListValues (const std::string& attributeName, std::list<const std::string*>& values) const = 0;
	// optional value range
	virtual bool getAttributeValueRange (const std::string& attributeName, double& minValue, double &maxValue) const = 0;
	// optional display name
	virtual UTF8StringPtr getDisplayName () const = 0;
};

//-----------------------------------------------------------------------------
/// @brief View creator interface adapter
//-----------------------------------------------------------------------------
class ViewCreatorAdapter : public IViewCreator
{
public:
	bool apply (CView* view, const UIAttributes& attributes, const IUIDescription* description) const override { return true; }
	bool getAttributeNames (std::list<std::string>& attributeNames) const override { return true; }
	AttrType getAttributeType (const std::string& attributeName) const override { return kUnknownType; }
	bool getAttributeValue (CView* view, const std::string& attributeName, std::string& stringValue, const IUIDescription* desc) const override { return false; }
	bool getPossibleListValues (const std::string& attributeName, std::list<const std::string*>& values) const override { return false; }
	bool getAttributeValueRange (const std::string& attributeName, double& minValue, double &maxValue) const override { return false; }
	UTF8StringPtr getDisplayName () const override { return getViewName (); }
};

} // namespace

#endif // __iviewcreator__
