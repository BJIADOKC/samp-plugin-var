#pragma once



#include "var.h"





class amxNatives
{

public:

	static const AMX_NATIVE_INFO varNatives[];

	static cell AMX_NATIVE_CALL SetPVarArrInt(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL SetPVarArrFloat(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL SetPVarArrString(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL GetPVarArrInt(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL GetPVarArrFloat(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL GetPVarArrString(AMX *amx, cell *params);

	static cell AMX_NATIVE_CALL SetGVarInt(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL SetGVarFloat(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL SetGVarString(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL GetGVarInt(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL GetGVarFloat(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL GetGVarString(AMX *amx, cell *params);

	static cell AMX_NATIVE_CALL SetGVarArrInt(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL SetGVarArrFloat(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL SetGVarArrString(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL GetGVarArrInt(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL GetGVarArrFloat(AMX *amx, cell *params);
	static cell AMX_NATIVE_CALL GetGVarArrString(AMX *amx, cell *params);
};