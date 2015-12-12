/*++

Copyright (c) 2013 Minoca Corp. All Rights Reserved

Module Name:

    dbgsym.h

Abstract:

    This header contains definitions for the higher level debugger symbol
    support.

Author:

    Evan Green 7-May-2013

--*/

//
// ---------------------------------------------------------------- Definitions
//

//
// ------------------------------------------------------ Data Type Definitions
//

//
// -------------------------------------------------------------------- Globals
//

//
// ------------------------------------------------------------------ Functions
//

PDEBUGGER_MODULE
DbgpFindModuleFromAddress (
    PDEBUGGER_CONTEXT Context,
    ULONGLONG Address,
    PULONGLONG DebasedAddress
    );

/*++

Routine Description:

    This routine attempts to locate a loaded module that corresponds to a
    virtual address in the target.

Arguments:

    Context - Supplies a pointer to the application context.

    Address - Supplies an address somewhere in one of the loaded modules.

    DebasedAddress - Supplies an optional pointer where the address minus the
        loaded base difference from where the module would have preferred to
        have been loaded will be returned. This will be the address from the
        symbols' perspective.

Return Value:

    Returns a pointer to the module that the address is contained in, or NULL if
    one cannot be found.

--*/

PDEBUGGER_MODULE
DbgpGetModule (
    PDEBUGGER_CONTEXT Context,
    PSTR ModuleName,
    ULONG MaxLength
    );

/*++

Routine Description:

    This routine gets a module given the module name.

Arguments:

    Context - Supplies a pointer to the application context.

    ModuleName - Supplies a null terminated string specifying the module name.

    MaxLength - Supplies the maximum length of the module name.

Return Value:

    Returns a pointer to the module, or NULL if one could not be found.

--*/

ULONGLONG
DbgpGetFunctionStartAddress (
    PDEBUGGER_CONTEXT Context,
    ULONGLONG Address
    );

/*++

Routine Description:

    This routine looks up the address for the beginning of the function given
    an address somewhere in the function.

Arguments:

    Context - Supplies a pointer to the application context.

    Address - Supplies a virtual address somewhere inside the function.

Return Value:

    Returns the address of the first instruction of the current function, or 0
    if the funtion could not be found.

--*/

BOOL
DbgpFindSymbol (
    PDEBUGGER_CONTEXT Context,
    PSTR SearchString,
    PSYMBOL_SEARCH_RESULT SearchResult
    );

/*++

Routine Description:

    This routine searches for symbols. Wildcards are accepted. If the search
    string is preceded by "modulename!" then only that module will be searched.

Arguments:

    Context - Supplies a pointer to the application context.

    SearchString - Supplies the string to search for.

    SearchResult - Supplies a pointer that receives symbol search result data.

Return Value:

    Returns TRUE on success, or FALSE on failure.

--*/

PDEBUGGER_MODULE
DbgpFindModuleFromEntry (
    PDEBUGGER_CONTEXT Context,
    PLOADED_MODULE_ENTRY TargetEntry
    );

/*++

Routine Description:

    This routine attempts to locate a loaded module that corresponds to the
    target's description of a loaded module.

Arguments:

    Context - Supplies a pointer to the application context.

    TargetEntry - Supplies the target's module description.

Return Value:

    Returns a pointer to the existing loaded module if one exists, or NULL if
    one cannot be found.

--*/

PDATA_SYMBOL
DbgpFindLocal (
    PDEBUGGER_CONTEXT Context,
    PSTR LocalName,
    ULONGLONG CurrentFrameInstructionPointer
    );

/*++

Routine Description:

    This routine searches the local variables and parameters in the function
    containing the given address for a variable matching the given name.

Arguments:

    Context - Supplies a pointer to the application context.

    LocalName - Supplies a case sensitive string of the local name.

    CurrentFrameInstructionPointer - Supplies the current frame instruction
        pointer.

Return Value:

    Returns a pointer to the local variable or function parameter symbol.

    NULL if no local variable matching the given name could be found.

--*/

PDATA_SYMBOL
DbgpGetLocal (
    PFUNCTION_SYMBOL Function,
    PSTR LocalName,
    ULONGLONG ExecutionAddress
    );

/*++

Routine Description:

    This routine gets the most up to date version of a local variable symbol.

Arguments:

    Function - Supplies a pointer to the function with the desired local
        variables.

    LocalName - Supplies a case sensitive string of the local name.

    ExecutionAddress - Supplies the current execution address. This function
        will attempt to find the local variable matching the LocalName whose
        minimum execution address is as close to ExecutionAddress as possible.
        It is assumed that this address has already been de-based (the current
        base address has been subtracted from it).

Return Value:

    Returns a pointer to the local variable symbol, or NULL if one could not
    be found.

--*/

BOOL
DbgpGetCurrentFunctionInformation (
    PDEBUGGER_CONTEXT Context,
    ULONGLONG CurrentFrameInstructionPointer,
    PFUNCTION_SYMBOL *Function,
    PULONGLONG ExecutionAddress
    );

/*++

Routine Description:

    This routine gets the function for the current instruction pointer and
    the module-adjusted execution address.

Arguments:

    Context - Supplies a pointer to the application context.

    CurrentFrameInstructionPointer - Supplies the current frame instruction
        pointer.

    Function - Supplies a pointer that receives symbol information for the
        current function.

    ExecutionAddress - Supplies a pointer that receives the current
        module-adjusted execution address.

Return Value:

    Returns TRUE on success, or FALSE on failure.

--*/

VOID
DbgpGetFriendlyName (
    PSTR FullName,
    ULONG FullNameLength,
    PSTR *NameBegin,
    PULONG NameLength
    );

/*++

Routine Description:

    This routine determines the portion of the given binary name to use as the
    friendly name.

Arguments:

    FullName - Supplies a pointer to the full path of the binary, null
        terminated.

    FullNameLength - Supplies the length of the full name buffer in bytes
        including the null terminator.

    NameBegin - Supplies a pointer where the beginning of the friendly name
        will be returned. This will point inside the full name.

    NameLength - Supplies a pointer where the number of characters in the
        friendly name will be returned, not including the null terminator.

Return Value:

    Returns TRUE on success, or FALSE on failure.

--*/

