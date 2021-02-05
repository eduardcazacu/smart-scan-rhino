////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN SetRefrence command
//

#pragma region SetRefrence command

#include "StdAfx.h"
#include "TestPlugIn.h"
#include "SmartScanService/SmartScanService.h"
#include "SmartScanService/Point3.h"


class CCommandSetRefrence : public CRhinoCommand
{
public:
	CCommandSetRefrence() = default;
	UUID CommandUUID() override
	{
		// {4D6E000F-AEFE-467C-A06B-36E62B7F153A}
		static const GUID SetRefrenceCommand_UUID =
		{ 0x4D6E000F, 0xAEFE, 0x467C, { 0xA0, 0x6B, 0x36, 0xE6, 0x2B, 0x7F, 0x15, 0x3A } };
		return SetRefrenceCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"SetRefrence"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;
};

// The one and only CCommandSetRefrence object
static class CCommandSetRefrence theSetRefrenceCommand;

extern SmartScan::SmartScanService obj;

CRhinoCommand::result CCommandSetRefrence::RunCommand(const CRhinoCommandContext& context)
{
	obj.CalibrateSingleRefPoint();
	return CRhinoCommand::success;
}

#pragma endregion

//
// END SetRefrence command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
