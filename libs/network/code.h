/*
** EPITECH PROJECT, 2023
** B-NWP-400-LIL-4-1-myteams-simon.riembault
** File description:
** code result
*/

#ifndef CODE_NETWORK_H
    #define CODE_NETWORK_H

    // Errors:
    #define ERROR 500
    #define UNFOUND 400
    #define UNAUTHORIZED 401
    #define UNKNOW_TEAM 402
    #define UNKNOW_CHANNEL 403
    #define UNKNOW_THREAD 404
    #define UNKNOW_USER 405
    #define ALREADY_EXIST 406
    #define LIST_MESSAGES_ERROR_CODE 407


    // Success:
    #define SUCCESS 200
    #define LIST_SUCCESS_CODE 201
    #define LOGIN_SUCCESS 202
    #define LOGOUT_SUCCESS 203
    #define USERS_SUCCESS_CODE 204
    #define CREATE_TEAM_SUCCESS 205
    #define CREATE_CHANNEL_SUCCESS 206
    #define CREATE_THREAD_SUCCESS 207
    #define CREATE_REPLY_SUCCESS 208
    #define USE_SUCCESS 209
    #define SUBSCRIBE_SUCCESS 210
    #define SUBSCRIBED_SUCCESS 211
    #define UNSUBSCRIBE_SUCCESS 212
    #define INFO_USER_GIVEN_SUCCESS 213
    #define MESSAGE_SENT 214
    #define LIST_MESSAGES_SUCCESS_CODE 215

    // Others:
    #define QUIT 0

#endif
