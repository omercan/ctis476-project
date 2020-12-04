#include "Federate.h"
#include <iostream>

Federate::Federate()
{
	rtiAmbassadorFactory = NULL;
	isConnected = false;
}

Federate::~Federate(void)
{
}

bool Federate::createAndJoinFederation(std::wstring& federationName, std::wstring& federateName, std::wstring& fomFile)
{
	rtiAmbassadorFactory = new rti1516e::RTIambassadorFactory();

	//create and join federation
	try {
		rtiAmbassador = rtiAmbassadorFactory->createRTIambassador();
		rtiAmbassador->connect(*this, rti1516e::HLA_EVOKED);
	}
	catch (rti1516e::Exception &e)
	{
		rtiAmbassador.reset();
		std::wcout << L"Error: " << e.what() << std::endl;
		return false;
	}

	try
	{
		rtiAmbassador->createFederationExecution(federationName, fomFile);
	}
	catch (rti1516e::FederationExecutionAlreadyExists &e)
	{
		std::wcout << L"federation execution already exists (" << e.what() << L")" << std::endl;
	}
	catch (rti1516e::Exception &e)
	{
		std::wcout << L"Error: " << e.what() << std::endl;
		return false;
	}

	try
	{
		federateHandle = rtiAmbassador->joinFederationExecution(federateName, federationName);
	}
	catch (rti1516e::Exception &e)
	{
		std::wcout << L"Error: " << e.what() << std::endl;
		return false;
	}

	return true;
}

bool Federate::resignAndDestroyFederation()
{
	//resign and leave federation
	try
	{
		rtiAmbassador->resignFederationExecution(rti1516e::ResignAction::NO_ACTION);
	}
	catch (rti1516e::Exception &e)
	{
		std::wcout << L"Error: " << e.what() << std::endl;
		return false;
	}

	try
	{
		rtiAmbassador->destroyFederationExecution(federationName);
	}
	catch (rti1516e::FederatesCurrentlyJoined &e)
	{
		std::wcout << L"cannot destroy: federates currently joined. (" << e.what() << L")" << std::endl;
	}
	catch (rti1516e::Exception &e)
	{
		std::wcout << L"Error: " << e.what() << std::endl;
		return false;
	}

	return true;
}

bool Federate::publishAndSubscribeAttributes()
{
	//subscribe your attribute
	try {
		rti1516e::ObjectClassHandle classHandle = rtiAmbassador->getObjectClassHandle(L"BaseEntity.PhysicaLEntity.Platform");
		rti1516e::AttributeHandleSet handleSet;
		rti1516e::AttributeHandle attr1 = rtiAmbassador->getAttributeHandle(classHandle, L"WorldLocation");
		rti1516e::AttributeHandle attr2 = rtiAmbassador->getAttributeHandle(classHandle, L"ForceIdentifier");
		rti1516e::AttributeHandle attr3 = rtiAmbassador->getAttributeHandle(classHandle, L"Orientation");
		rti1516e::AttributeHandle attr4 = rtiAmbassador->getAttributeHandle(classHandle, L"DamageState");
		rti1516e::AttributeHandle attr5 = rtiAmbassador->getAttributeHandle(classHandle, L"BrakeLightsOn");
		rti1516e::AttributeHandle attr6 = rtiAmbassador->getAttributeHandle(classHandle, L"InteriorLightsOn");

		handleSet.insert(attr1);
		handleSet.insert(attr2);
		handleSet.insert(attr3);
		handleSet.insert(attr4);
		handleSet.insert(attr5);
		handleSet.insert(attr6);

		rtiAmbassador->subscribeObjectClassAttributes(classHandle, handleSet);
	}
	catch (rti1516e::Exception& e) {
		std::wcout << L"Error: " << e.what() << std::endl;
		return false;
	}

	return true;
}

void Federate::swapData(unsigned char* data, int size)
{
	if (size <= 1)
	{
		return;
	}

	register int i = 0;
	register int j = size - 1;
	while (i < j)
	{
		std::swap(data[i], data[j]);
		i++;
		j--;
	}
}
void Federate::evoke()
{
	rtiAmbassador->evokeMultipleCallbacks(0.1, 0.2);
}

// NullFederateAmbassador
void Federate::discoverObjectInstance(rti1516e::ObjectInstanceHandle objectInstanceHandle, rti1516e::ObjectClassHandle objectClassHandle, std::wstring const& objectInstanceName) throw(rti1516e::FederateInternalError)
{
	//do discover operations
	auto className = rtiAmbassador->getObjectClassName(objectClassHandle);
	std::wcout << L"Object Created (Class: " << className << L") (InstanceName: " << objectInstanceName << L")" << std::endl;
}

void Federate::discoverObjectInstance(rti1516e::ObjectInstanceHandle objectInstanceHandle, rti1516e::ObjectClassHandle objectClassHandle, std::wstring const& objectInstanceName, rti1516e::FederateHandle producingFederate) throw(rti1516e::FederateInternalError)
{
	//do discover operations
	auto className = rtiAmbassador->getObjectClassName(objectClassHandle);
	std::wcout << L"Object Created (Class: " << className << L") (InstanceName: " << objectInstanceName << L")" << std::endl;
}

void Federate::removeObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::SupplementalRemoveInfo theRemoveInfo) throw(rti1516e::FederateInternalError)
{
	//do remove operations
	auto objectInstanceName = rtiAmbassador->getObjectInstanceName(object);
	auto objectClassHandle = rtiAmbassador->getKnownObjectClassHandle(object);
	auto className = rtiAmbassador->getObjectClassName(objectClassHandle);
	std::wcout << L"Object Removed (Class: " << className << L") (InstanceName: " << objectInstanceName << L")" << std::endl;

}
void Federate::removeObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::LogicalTime const& time, rti1516e::OrderType receivedOrder, rti1516e::SupplementalRemoveInfo theRemoveInfo) throw(rti1516e::FederateInternalError)
{
	//do remove operations
	auto objectInstanceName = rtiAmbassador->getObjectInstanceName(object);
	auto objectClassHandle = rtiAmbassador->getKnownObjectClassHandle(object);
	auto className = rtiAmbassador->getObjectClassName(objectClassHandle);
	std::wcout << L"Object Removed (Class: " << className << L") (InstanceName: " << objectInstanceName << L")" << std::endl;
}
void Federate::removeObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::LogicalTime const& time, rti1516e::OrderType receivedOrder, rti1516e::MessageRetractionHandle handle, rti1516e::SupplementalRemoveInfo theRemoveInfo) throw(rti1516e::FederateInternalError)
{
	//do remove operations
	auto objectInstanceName = rtiAmbassador->getObjectInstanceName(object);
	auto objectClassHandle = rtiAmbassador->getKnownObjectClassHandle(object);
	auto className = rtiAmbassador->getObjectClassName(objectClassHandle);
	std::wcout << L"Object Removed (Class: " << className << L") (InstanceName: " << objectInstanceName << L")" << std::endl;
}

void Federate::reflectAttributeValues(rti1516e::ObjectInstanceHandle object, rti1516e::AttributeHandleValueMap const& attributeValues, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::TransportationType type, rti1516e::SupplementalReflectInfo reflectInfo) throw (rti1516e::FederateInternalError)
{
	handleAttributeReflection(object, attributeValues);
}
void Federate::reflectAttributeValues(rti1516e::ObjectInstanceHandle object, rti1516e::AttributeHandleValueMap const& attributeValues, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::TransportationType type, rti1516e::LogicalTime const & time, rti1516e::OrderType receivedOrder, rti1516e::SupplementalReflectInfo reflectInfo) throw (rti1516e::FederateInternalError)
{
	handleAttributeReflection(object, attributeValues);
}
void Federate::reflectAttributeValues(rti1516e::ObjectInstanceHandle object, rti1516e::AttributeHandleValueMap const& attributeValues, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::TransportationType type, rti1516e::LogicalTime const & time, rti1516e::OrderType receivedOrder, rti1516e::MessageRetractionHandle theHandle, rti1516e::SupplementalReflectInfo reflectInfo) throw (rti1516e::FederateInternalError)
{
	handleAttributeReflection(object, attributeValues);
}

void Federate::handleAttributeReflection(rti1516e::ObjectInstanceHandle object, rti1516e::AttributeHandleValueMap const& attributes)
{
	//Do attribute handling
	for (auto it = attributes.begin(); it != attributes.end(); it++)
	{
		auto attributeHandle = it->first;
		auto objectInstanceName = rtiAmbassador->getObjectInstanceName(object);
		auto objectClassHandle = rtiAmbassador->getKnownObjectClassHandle(object);
		auto className = rtiAmbassador->getObjectClassName(objectClassHandle);
		auto attributeName = rtiAmbassador->getAttributeName(objectClassHandle, attributeHandle);

		if (attributeName == L"ForceIdentifier")
		{
			char forceIdentifier = *(static_cast<const char*>(it->second.data()));
			std::wstring value;
			switch (forceIdentifier)
			{
			case 0:
				value = L"Other";
				break;
			case 1:
				value = L"Friendly";
				break;
			case 2:
				value = L"Opposing";
				break;
			case 3:
				value = L"Neutral";
				break;
			default:
				value = L"UNKNOWN";
				break;
			}

			std::wcout << L"Attributes Reflected (Class: " << className << L") (InstanceName: " << objectInstanceName << L") (ForceIdentifier: " << value << ")" << std::endl;
		}
		else if (attributeName == L"DamageState")
		{
			int damageState = *(static_cast<const int*>(it->second.data()));
			SwapLittleEndian(damageState);

			std::wstring value;
			switch (damageState)
			{
			case 0:
				value = L"No Damage";
				break;
			case 1:
				value = L"Slight Damage";
				break;
			case 2:
				value = L"Moderate Damage";
				break;
			case 3:
				value = L"Destroyed";
				break;
			default:
				value = L"UNKNOWN";
				break;
			}

			std::wcout << L"Attributes Reflected (Class: " << className << L") (InstanceName: " << objectInstanceName << L") (DamageState: " << value << L")" << std::endl;
		}
		else if (attributeName == L"WorldLocation")
		{
			double x, y, z;
			char* data = (char*)((it->second.data()));
			memcpy(&x, data, sizeof(double));
			data += sizeof(double);
			memcpy(&y, data, sizeof(double));
			data += sizeof(double);
			memcpy(&z, data, sizeof(double));
			data += sizeof(double);
			SwapLittleEndian(x);
			SwapLittleEndian(y);
			SwapLittleEndian(z);

			std::wcout << L"Attributes Reflected (Class: " << className << L") (InstanceName: " << objectInstanceName << L") (WorldLocation: (x: " << x << L") (y: " << y << L") (z: " << z << ")" << std::endl;
		}
		else if (attributeName == L"Orientation")
		{
			//X means Psi
			//Y means Theta
			//Z means Phi
			float x, y, z;
			char* data = (char*)((it->second.data()));
			memcpy(&x, data, sizeof(float));
			data += sizeof(float);
			memcpy(&y, data, sizeof(float));
			data += sizeof(float);
			memcpy(&z, data, sizeof(float));
			data += sizeof(float);
			SwapLittleEndian(x);
			SwapLittleEndian(y);
			SwapLittleEndian(z);

			std::wcout << L"Attributes Reflected (Class: " << className << L") (InstanceName: " << objectInstanceName << L") (Orientation: (Psi: " << x << L") (Theta: " << y << L") (Phi: " << z << ")" << std::endl;
		}
		else if (attributeName == L"BrakeLightsOn")
		{
			bool value = *(static_cast<const bool*>(it->second.data()));

			std::wcout << L"Attributes Reflected (Class: " << className << L") (InstanceName: " << objectInstanceName << L") (BrakeLightsOn: " << value << L")" << std::endl;
		}
		else if (attributeName == L"InteriorLightsOn")
		{
			bool value = *(static_cast<const bool*>(it->second.data()));

			std::wcout << L"Attributes Reflected (Class: " << className << L") (InstanceName: " << objectInstanceName << L") (InteriorLightsOn: " << value << L")" << std::endl;
		}
	}
}
