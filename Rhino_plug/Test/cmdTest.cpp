// cmdTest.cpp : command file
//



#include "StdAfx.h"
#include "TestPlugIn.h"
#include "SmartScanService/SmartScanService.h"
#include "SmartScanService/Point3.h"



#include <iostream>
#include <fstream>

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
//
// BEGIN makepoint command
//

#pragma region Beginscan command

class CCommandBeginscan : public CRhinoCommand
{
public:
	CCommandBeginscan() = default;
	UUID CommandUUID() override
	{
		// {D48259EA-6337-4B0A-9BE6-424C9E60A0CF}
		static const GUID BeginscanCommand_UUID =
		{ 0xD48259EA, 0x6337, 0x4B0A, { 0x9B, 0xE6, 0x42, 0x4C, 0x9E, 0x60, 0xA0, 0xCF } };
		return BeginscanCommand_UUID;
	}
	const wchar_t* EnglishCommandName() override { return L"Beginscan"; }
	CRhinoCommand::result RunCommand(const CRhinoCommandContext& context) override;


};

// The one and only CCommandmakepoint object
static class CCommandBeginscan theBeginscanCommand;
int temp = 0;
std::shared_ptr<CRhinoCommandContext> pContext;

SmartScan::SmartScanService obj(false);
extern int Stopcommand;

std::vector<int> sensorsUsed = { 0,1 };
ON_wString str;
CRhinoPointCloudObject* object;
std::vector<ON_3dPoint> RhinoVector;

void TestUICallback(std::vector<SmartScan::Point3>& data)
{
	pContext->m_doc.DeleteObject(object);
	RhinoVector.clear();

	for (auto d : data)
	{
		RhinoVector.emplace_back(ON_3dPoint(d.x,d.y,d.z));
	}

	

	object = pContext->m_doc.AddPointCloudObject(RhinoVector.size(), &RhinoVector[0]);
	pContext->m_doc.Redraw();
	
	

	if (Stopcommand == 1)
	{


		str.Format(L"The buffer has \"%i\" Points.\n", data.size());
		RhinoApp().Print(str);
		Stopcommand = 0;
	}

}




CRhinoCommand::result CCommandBeginscan::RunCommand(const CRhinoCommandContext& context)
{


	pContext = std::make_shared<CRhinoCommandContext>(context);
	ON_wString str;

	obj.RegisterNewDataCallback(TestUICallback);
	int sizee = obj.GetScansList().size();
	obj.SetFilteringPrecision(4);
	obj.StartScan(sensorsUsed);

	




	
	
	return CRhinoCommand::success;
}

#pragma endregion



//
// END Test command
//
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
