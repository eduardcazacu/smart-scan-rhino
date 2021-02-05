////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN InitAndCali command
//
#include "StdAfx.h"
#include "TestPlugIn.h"
#include "SmartScanService/SmartScanService.h"
#include "SmartScanService/Point3.h"

#pragma region InitAndCali command

class CCommandInitAndCali : public CRhinoCommand
{
public:
	CCommandInitAndCali() = default;
	UUID CommandUUID() override
	{
		// {80F30B82-177F-4564-95FD-2EE8D9BC8284}
		static const GUID InitAndCaliCommand_UUID =
		{ 0x80F30B82, 0x177F, 0x4564, { 0x95, 0xFD, 0x2E, 0xE8, 0xD9, 0xBC, 0x82, 0x84 } };
		return InitAndCaliCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"InitAndCali"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandInitAndCali object
std::shared_ptr<CRhinoCommandContext> p2Context;
static class CCommandInitAndCali theInitAndCaliCommand;
extern SmartScan::SmartScanService obj;

#include <fstream>


CRhinoCommand::result CCommandInitAndCali::RunCommand(const CRhinoCommandContext& context)
{
	p2Context = std::make_shared<CRhinoCommandContext>(context);

	obj.Init();
	obj.NewScan({ 0,1 }, 2);
	
	
	return CRhinoCommand::success;
}

#pragma endregion

//
// END InitAndCali command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
