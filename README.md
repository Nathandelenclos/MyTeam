# My_Teams Protocol
***
## Serveur
### Usage
```bash
./myteams_server port
```
- port is the port number on which the server socket listens.
***
## Command Line Interface (CLI) Client
### Usage launching client
```bash
./myteams_client ip port
```
- ip is the server ip address on which the server socket listens
- port is the port number on which the server socket listens
### Usage commands in client
```bash
/help
```
show help
```bash
/login [“user_name”]
```
set the user_name used by client
```bash
/logout
```
disconnect the client from the server
```bash
/users
```
get the list of all users that exist on the domain
```bash
/user [“user_uuid”]
```
get information about a user
```bash
/send [“user_uuid”] [“message_body”]
```
send a message to a user
```bash
/messages [“user_uuid”]
```
list all messages exchange with an user
```bash
/subscribe [“team_uuid”]
```
subscribe to the event of a team and its sub directories (enable reception of all events from a team)
```bash
/subscribed ?[“team_uuid”]
```
list all subscribed teams or list all users subscribed to a team
```bash
/unsubscribe [“team_uuid”]
```
unsubscribe from a team
```bash
/use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”]
```
use specify a context team/channel/thread
```bash
/create [“team_name”] [“team_description”]
```
create a new team when the context is not defined (/use)
```bash
/create [“channel_name”] [“channel_description”]
```
create a new channel when team_uuid is defined (/use “team_uuid”)
```bash
/create [“thread_title”] [“thread_message”]
```
create a new thread when team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”)
```bash
/create [“comment_body”]
```
create a new reply when team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”)
```bash
/list
```
- list all existing teams when the context is not defined (/use)
- list all existing channels when team_uuid is defined (/use “team_uuid”)
- list all existing threads when team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”)
- list all existing replies when team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”)
```bash
/info
```
- display currently logged user infos when the context is not defined (/use)
- display currently selected team infos when team_uuid is defined (/use “team_uuid”)
- display currently selected channel infos when team_uuid and channel_uuid are defined (/use “team_uuid” “channel_uuid”)
- display currently selected thread infos when team_uuid, channel_uuid and thread_uuid are defined (/use “team_uuid” “channel_uuid” “thread_uuid”)
