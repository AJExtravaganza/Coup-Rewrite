#pragma once

enum Role
{
    NullRole,
    DUKE,
    ASSASSIN,
    AMBASSADOR,
    CAPTAIN,
    CONTESSA
};

enum ActionID
{
    NullAction,
    INCOME,
    FOREIGN_AID,
    COUP,
    TAX,
    ASSASSINATE,
    EXCHANGE,
    STEAL
};

enum ActionStatus
{
    NullStatus,
    VALID,
    INSUFFICIENTFUNDS,
    CHALLENGED,
    BLOCKED,
    RESOLVED
};
