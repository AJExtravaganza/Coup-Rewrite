#pragma once

// TODO (Backbox#1#): Cull as necessary upon completion of project
enum Role
{
    NullRole,
    DUKE,
    ASSASSIN,
    AMBASSADOR,
    CAPTAIN,
    CONTESSA,
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
    STEAL,
    BLOCK_FOREIGN_AID,
    BLOCK_ASSASSINATE,
    BLOCK_STEAL_CAPTAIN,
    BLOCK_STEAL_AMBASSADOR,
    CHALLENGE,
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
