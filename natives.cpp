#pragma once



#include "natives.h"





boost::unordered_map<int, boost::unordered_map<std::string, boost::unordered_map<long, amxVars> > > pVarArrPool;

boost::unordered_map<std::string, amxVars> gVarPool;
boost::unordered_map<std::string, boost::unordered_map<long, amxVars> > gVarArrPool;

boost::unordered_map<std::string, boost::unordered_map<long, amxVars> > tmpVar;
boost::unordered_map<long, amxVars> tmpKey;


extern logprintf_t logprintf;





const AMX_NATIVE_INFO amxNatives::varNatives[] =
{
	{"SetPVarArrInt", amxNatives::SetPVarArrInt},
	{"SetPVarArrFloat", amxNatives::SetPVarArrFloat},
	{"SetPVarArrString", amxNatives::SetPVarArrString},
	{"GetPVarArrInt", amxNatives::GetPVarArrInt},
	{"GetPVarArrFloat", amxNatives::GetPVarArrFloat},
	{"GetPVarArrString", amxNatives::GetPVarArrString},

	{"SetGVarInt", amxNatives::SetGVarInt},
	{"SetGVarFloat", amxNatives::SetGVarFloat},
	{"SetGVarString", amxNatives::SetGVarString},
	{"GetGVarInt", amxNatives::GetGVarInt},
	{"GetGVarFloat", amxNatives::GetGVarFloat},
	{"GetGVarString", amxNatives::GetGVarString},

	{"SetGVarArrInt", amxNatives::SetGVarArrInt},
	{"SetGVarArrFloat", amxNatives::SetGVarArrFloat},
	{"SetGVarArrString", amxNatives::SetGVarArrString},
	{"GetGVarArrInt", amxNatives::GetGVarArrInt},
	{"GetGVarArrFloat", amxNatives::GetGVarArrFloat},
	{"GetGVarArrString", amxNatives::GetGVarArrString},

	{NULL, NULL}
};



// native SetPVarArrInt(playerid, varname[], value, index = 0);
cell AMX_NATIVE_CALL amxNatives::SetPVarArrInt(AMX *amx, cell *params)
{
	if(!arguments(4))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'SetPVarArrInt'", (params[0] >> 2));

		return NULL;
	}

	int playerid = params[1];
	char *varname = NULL;

	amx_StrParam(amx, params[2], varname);

	long index = params[4];
	
	amxVars push;

	if(pVarArrPool.count(playerid))
		tmpVar = pVarArrPool.find(playerid)->second;

	if(tmpVar.count(varname))
		tmpKey = tmpVar.find(varname)->second;

	push.integer = params[3];

	tmpKey[index] = push;
	tmpVar[varname] = tmpKey;
	pVarArrPool[playerid] = tmpVar;

	return 1;
}



// native SetPVarArrFloat(playerid, varname[], Float:value, index = 0);
cell AMX_NATIVE_CALL amxNatives::SetPVarArrFloat(AMX *amx, cell *params)
{
	if(!arguments(4))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'SetPVarArrFloat'", (params[0] >> 2));

		return NULL;
	}

	int playerid = params[1];
	char *varname = NULL;

	amx_StrParam(amx, params[2], varname);

	long index = params[4];
	
	amxVars push;

	if(pVarArrPool.count(playerid))
		tmpVar = pVarArrPool.find(playerid)->second;

	if(tmpVar.count(varname))
		tmpKey = tmpVar.find(varname)->second;

	push.floating = amx_ctof(params[3]);

	tmpKey[index] = push;
	tmpVar[varname] = tmpKey;
	pVarArrPool[playerid] = tmpVar;

	return 1;
}



// native SetPVarArrString(playerid, varname[], value[], index = 0);
cell AMX_NATIVE_CALL amxNatives::SetPVarArrString(AMX *amx, cell *params)
{
	if(!arguments(4))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'SetPVarArrString'", (params[0] >> 2));

		return NULL;
	}

	int playerid = params[1];
	char *varname = NULL;
	char *value = NULL;

	amx_StrParam(amx, params[2], varname);
	amx_StrParam(amx, params[3], value);

	long index = params[4];
	
	amxVars push;

	if(pVarArrPool.count(playerid))
		tmpVar = pVarArrPool.find(playerid)->second;

	if(tmpVar.count(varname))
		tmpKey = tmpVar.find(varname)->second;

	push.string = value;

	tmpKey[index] = push;
	tmpVar[varname] = tmpKey;
	pVarArrPool[playerid] = tmpVar;

	return 1;
}



// native GetPVarArrInt(playerid, varname[], index = 0);
cell AMX_NATIVE_CALL amxNatives::GetPVarArrInt(AMX *amx, cell *params)
{
	if(!arguments(3))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'GetPVarArrInt'", (params[0] >> 2));

		return NULL;
	}

	int playerid = params[1];
	char *varname = NULL;
	long index = params[3];

	amx_StrParam(amx, params[2], varname);

	if(!pVarArrPool.count(playerid))
		return 0;

	if(!pVarArrPool.find(playerid)->second.count(varname))
		return 0;

	if(!pVarArrPool.find(playerid)->second.find(varname)->second.count(index))
		return 0;

	return pVarArrPool.find(playerid)->second.find(varname)->second.find(index)->second.integer;
}



// native Float:GetPVarArrFloat(playerid, varname[], index = 0);
cell AMX_NATIVE_CALL amxNatives::GetPVarArrFloat(AMX *amx, cell *params)
{
	if(!arguments(3))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'GetPVarArrFloat'", (params[0] >> 2));

		return NULL;
	}

	int playerid = params[1];
	char *varname = NULL;
	long index = params[3];
	float value = 0.0f;

	amx_StrParam(amx, params[2], varname);

	if(!pVarArrPool.count(playerid))
		return amx_ftoc(value);

	if(!pVarArrPool.find(playerid)->second.count(varname))
		return amx_ftoc(value);

	if(!pVarArrPool.find(playerid)->second.find(varname)->second.count(index))
		return amx_ftoc(value);

	value = pVarArrPool.find(playerid)->second.find(varname)->second.find(index)->second.floating;

	return amx_ftoc(value);
}



// native GetPVarArrString(playerid, varname[], dest[], index = 0, size = sizeof dest);
cell AMX_NATIVE_CALL amxNatives::GetPVarArrString(AMX *amx, cell *params)
{
	if(!arguments(5))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'GetPVarArrString'", (params[0] >> 2));

		return NULL;
	}

	int playerid = params[1];
	char *varname = NULL;
	cell *dest = NULL;
	long index = params[4];

	amx_StrParam(amx, params[2], varname);
	amx_GetAddr(amx, params[3], &dest);

	if(!pVarArrPool.count(playerid))
		return 0;

	if(!pVarArrPool.find(playerid)->second.count(varname))
		return 0;

	if(!pVarArrPool.find(playerid)->second.find(varname)->second.count(index))
		return 0;

	amx_SetString(dest, pVarArrPool.find(playerid)->second.find(varname)->second.find(index)->second.string.c_str(), NULL, NULL, params[5]);

	return 1;
}



// native SetGVarInt(varname[], value);
cell AMX_NATIVE_CALL amxNatives::SetGVarInt(AMX *amx, cell *params)
{
	if(!arguments(2))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'SetGVarInt'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;

	amxVars push;

	amx_StrParam(amx, params[1], varname);
	push.integer = params[2];

	gVarPool[varname] = push;

	return 1;
}



// native SetGVarFloat(varname[], Float:value);
cell AMX_NATIVE_CALL amxNatives::SetGVarFloat(AMX *amx, cell *params)
{
	if(!arguments(2))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'SetGVarFloat'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;

	amxVars push;

	amx_StrParam(amx, params[1], varname);
	push.floating = amx_ctof(params[2]);

	gVarPool[varname] = push;

	return 1;
}



// native SetGVarString(varname[], value[]);
cell AMX_NATIVE_CALL amxNatives::SetGVarString(AMX *amx, cell *params)
{
	if(!arguments(2))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'SetGVarString'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;
	char *value = NULL;

	amxVars push;

	amx_StrParam(amx, params[1], varname);
	amx_StrParam(amx, params[2], value);
	push.string = value;

	gVarPool[varname] = push;

	return 1;
}



// native GetGVarInt(varname[]);
cell AMX_NATIVE_CALL amxNatives::GetGVarInt(AMX *amx, cell *params)
{
	if(!arguments(1))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'GetGVarInt'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;

	amx_StrParam(amx, params[1], varname);

	if(!gVarPool.count(varname))
		return 0;

	return gVarPool.find(varname)->second.integer;
}



// native Float:GetGVarFloat(varname[]);
cell AMX_NATIVE_CALL amxNatives::GetGVarFloat(AMX *amx, cell *params)
{
	if(!arguments(1))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'GetGVarFloat'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;
	float value = 0.0f;

	amx_StrParam(amx, params[1], varname);

	if(!gVarPool.count(varname))
		return amx_ftoc(value);

	value = gVarPool.find(varname)->second.floating;

	return amx_ftoc(value);
}



// native GetGVarString(varname[], dest[], size = sizeof dest);
cell AMX_NATIVE_CALL amxNatives::GetGVarString(AMX *amx, cell *params)
{
	if(!arguments(3))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'GetGVarString'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;
	cell *dest = NULL;

	amx_StrParam(amx, params[1], varname);
	amx_GetAddr(amx, params[2], &dest);

	if(!gVarPool.count(varname))
		return 0;

	amx_SetString(dest, gVarPool.find(varname)->second.string.c_str(), NULL, NULL, params[3]);

	return 1;
}



// native SetGVarArrInt(varname[], value, index = 0);
cell AMX_NATIVE_CALL amxNatives::SetGVarArrInt(AMX *amx, cell *params)
{
	if(!arguments(3))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'SetGVarArrInt'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;
	long index = params[3];

	amxVars push;

	amx_StrParam(amx, params[1], varname);

	if(gVarArrPool.count(varname))
		tmpKey = gVarArrPool.find(varname)->second;

	push.integer = params[2];

	tmpKey[index] = push;
	gVarArrPool[varname] = tmpKey;

	return 1;
}



// native SetGVarArrFloat(varname[], Float:value, index = 0);
cell AMX_NATIVE_CALL amxNatives::SetGVarArrFloat(AMX *amx, cell *params)
{
	if(!arguments(3))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'SetGVarArrFloat'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;
	long index = params[3];

	amxVars push;

	amx_StrParam(amx, params[1], varname);

	if(gVarArrPool.count(varname))
		tmpKey = gVarArrPool.find(varname)->second;

	push.floating = amx_ctof(params[2]);

	tmpKey[index] = push;
	gVarArrPool[varname] = tmpKey;

	return 1;
}



// native SetGVarArrString(varname[], value[], index = 0);
cell AMX_NATIVE_CALL amxNatives::SetGVarArrString(AMX *amx, cell *params)
{
	if(!arguments(3))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'SetGVarArrString'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;
	char *value = NULL;
	long index = params[3];

	amxVars push;

	amx_StrParam(amx, params[1], varname);
	amx_StrParam(amx, params[2], value);

	if(gVarArrPool.count(varname))
		tmpKey = gVarArrPool.find(varname)->second;

	push.string = value;

	tmpKey[index] = push;
	gVarArrPool[varname] = tmpKey;

	return 1;
}



// native GetGVarArrInt(varname[], index = 0);
cell AMX_NATIVE_CALL amxNatives::GetGVarArrInt(AMX *amx, cell *params)
{
	if(!arguments(2))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'GetGVarArrInt'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;
	long index = params[2];

	amx_StrParam(amx, params[1], varname);

	if(!gVarArrPool.count(varname))
		return 0;

	if(!gVarArrPool.find(varname)->second.count(index))
		return 0;

	return gVarArrPool.find(varname)->second.find(index)->second.integer;
}



// native Float:GetGVarArrFloat(varname[], index = 0);
cell AMX_NATIVE_CALL amxNatives::GetGVarArrFloat(AMX *amx, cell *params)
{
	if(!arguments(2))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'GetGVarArrFloat'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;
	long index = params[2];
	float value = 0.0f;

	amx_StrParam(amx, params[1], varname);

	if(!gVarArrPool.count(varname))
		return amx_ftoc(value);

	if(!gVarArrPool.find(varname)->second.count(index))
		return amx_ftoc(value);

	value = gVarArrPool.find(varname)->second.find(index)->second.floating;

	return amx_ftoc(value);
}



// native GetGVarArrString(varname[], dest[], index = 0, size = sizeof dest);
cell AMX_NATIVE_CALL amxNatives::GetGVarArrString(AMX *amx, cell *params)
{
	if(!arguments(4))
	{
		logprintf("Var plugin: Invalid argument count (%i) in native 'GetGVarArrString'", (params[0] >> 2));

		return NULL;
	}

	char *varname = NULL;
	cell *dest = NULL;
	long index = params[3];

	amx_StrParam(amx, params[1], varname);
	amx_GetAddr(amx, params[2], &dest);

	if(!gVarArrPool.count(varname))
		return 0;

	if(!gVarArrPool.find(varname)->second.count(index))
		return 0;

	amx_SetString(dest, gVarArrPool.find(varname)->second.find(index)->second.string.c_str(), NULL, NULL, params[4]);

	return 1;
}