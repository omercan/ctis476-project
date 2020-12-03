#include <stdio.h>
#include <iostream>
#include "Federate.h"
#include <string>
#include <windows.h>
int main(int argc, char *argv[])
{
	Federate f;
	std::wstring federationName = L"RPRServer";
	std::wstring federateName = L"SimpleListener";
	std::wstring fomFile = L"RPR-FOM.fed";

	bool success = true;

	if (f.createAndJoinFederation(federationName, federateName, fomFile))
	{
		std::wcout << L"Connected to Federation: " << federationName << std::endl;
	}
	else
	{
		std::wcout << L"Connection to Federation : " << federationName << L" failed" << std::endl;
		success = false;
	}

	if (success)
	{
		if (f.publishAndSubscribeAttributes())
		{
			std::wcout << L"Subscribed Attributes" << std::endl;
		}
		else
		{
			std::wcout << L"Subscription to Attributes failed" << std::endl;
			success = false;
		}
	}

	while (success)
	{
		f.evoke();
		Sleep(10);
	}

	system("Pause");
}