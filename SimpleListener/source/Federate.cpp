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
		return false;
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
	return true;
}

void Federate::swapData(unsigned char* data, int size)
{
	if(size <= 1)
		return;

	register int i = 0;
	register int j = size-1;
	while (i<j)
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
}

void Federate::discoverObjectInstance(rti1516e::ObjectInstanceHandle objectInstanceHandle, rti1516e::ObjectClassHandle objectClassHandle, std::wstring const& objectInstanceName, rti1516e::FederateHandle producingFederate) throw(rti1516e::FederateInternalError)
{
	//do discover operations
}

void Federate::removeObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::SupplementalRemoveInfo theRemoveInfo) throw(rti1516e::FederateInternalError)
{
	//do remove operations
}
void Federate::removeObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::LogicalTime const& time, rti1516e::OrderType receivedOrder, rti1516e::SupplementalRemoveInfo theRemoveInfo) throw(rti1516e::FederateInternalError)
{
	//do remove operations
}
void Federate::removeObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::LogicalTime const& time, rti1516e::OrderType receivedOrder, rti1516e::MessageRetractionHandle handle, rti1516e::SupplementalRemoveInfo theRemoveInfo) throw(rti1516e::FederateInternalError)
{
	//do remove operations
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
}