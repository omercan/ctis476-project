#pragma once
#include "RTI/RTIambassadorFactory.h"
#include "RTI/NullFederateAmbassador.h"
#include "RTI/RTI1516.h"
#include <memory>

#define SwapLittleEndian(x) Federate::swapData((unsigned char*)&x, sizeof(x))

class Federate : public rti1516e::NullFederateAmbassador
{
public:
	Federate();
	~Federate(void);
	static void swapData(unsigned char* data, int size);

public:
	bool createAndJoinFederation(std::wstring& federationName, std::wstring& federateName, std::wstring& fomFile);
	bool resignAndDestroyFederation();
	bool publishAndSubscribeAttributes();

	void evoke();
	
public: // NullFederateAmbassador
	void discoverObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::ObjectClassHandle objectClass, std::wstring const& objectInstanceName) throw(rti1516e::FederateInternalError);
	void discoverObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::ObjectClassHandle objectClass, std::wstring const& objectInstanceName, rti1516e::FederateHandle producingFederate) throw(rti1516e::FederateInternalError);

	void removeObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::SupplementalRemoveInfo theRemoveInfo) throw(rti1516e::FederateInternalError);
	void removeObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::LogicalTime const& time, rti1516e::OrderType receivedOrder, rti1516e::SupplementalRemoveInfo theRemoveInfo) throw(rti1516e::FederateInternalError);
	void removeObjectInstance(rti1516e::ObjectInstanceHandle object, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::LogicalTime const& time, rti1516e::OrderType receivedOrder, rti1516e::MessageRetractionHandle handle, rti1516e::SupplementalRemoveInfo theRemoveInfo) throw(rti1516e::FederateInternalError);

	void reflectAttributeValues(rti1516e::ObjectInstanceHandle object, rti1516e::AttributeHandleValueMap const& attributeValues, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::TransportationType type, rti1516e::SupplementalReflectInfo reflectInfo) throw (rti1516e::FederateInternalError);
	void reflectAttributeValues(rti1516e::ObjectInstanceHandle object, rti1516e::AttributeHandleValueMap const& attributeValues, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::TransportationType type, rti1516e::LogicalTime const & time, rti1516e::OrderType receivedOrder, rti1516e::SupplementalReflectInfo reflectInfo) throw (rti1516e::FederateInternalError);
	void reflectAttributeValues(rti1516e::ObjectInstanceHandle object, rti1516e::AttributeHandleValueMap const& attributeValues, rti1516e::VariableLengthData const& userSuppliedTag, rti1516e::OrderType sentOrder, rti1516e::TransportationType type, rti1516e::LogicalTime const & time, rti1516e::OrderType receivedOrder, rti1516e::MessageRetractionHandle theHandle, rti1516e::SupplementalReflectInfo reflectInfo) throw (rti1516e::FederateInternalError);

private:
	void handleAttributeReflection(rti1516e::ObjectInstanceHandle object, rti1516e::AttributeHandleValueMap const& attributes);
private:
	std::auto_ptr < rti1516e::RTIambassador > rtiAmbassador;
	rti1516e::FederateHandle federateHandle;
	rti1516e::RTIambassadorFactory* rtiAmbassadorFactory;

	std::wstring federationName;
	std::wstring federateName;
	bool isConnected;
};

