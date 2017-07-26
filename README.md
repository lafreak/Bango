# Bango [![Build Status](https://travis-ci.org/lafreak/Bango.svg?branch=master)](https://travis-ci.org/lafreak/Bango)
KalOnline MMORPG Server Emulator written in C++ for Linux 64bit OS.  

## Quick installation
Install MySQL Server: `sudo apt-get install mysql-server`  
Install Libzdb: `sudo apt-get install libzdb-dev`  
Run `\. build.sql` in your database.

## Getting started
https://github.com/lafreak/Bango/wiki/Getting-started

## Documentation
- [CNPC](https://github.com/lafreak/Bango/blob/master/doc/API.md#class-cnpc)
- [CParty](https://github.com/lafreak/Bango/blob/master/doc/API.md#class-cparty)
- [CTile](https://github.com/lafreak/Bango/blob/master/doc/API.md#class-ctile)
- [CZone](https://github.com/lafreak/Bango/blob/master/doc/API.md#class-czone)

## Progress

###### Player
- [x] Movement
- [x] Rest
- [x] Start from village
- [ ] EXP cutdown
- [x] Property update
- [x] Stats distrubtion
- [x] Normal chatting
- [x] Teleportation
- [x] Animation
- [x] Load/save skillbar shortcuts
- [x] Base attack
- [x] Damage, evade calculation
- [x] Final stats calculation
- [ ] Trade
- [ ] Stall
- [ ] Guild

###### Skills
- [ ] Load from database
- [ ] Learn skills

###### Party
- [x] Invitation
- [x] Decline
- [x] Expulsion
- [x] Member minimap position broadcast
- [x] Member HP/Level broadcast
- [x] Chatting

###### Item
- [x] Load invitentory from database
- [x] Insert
- [x] Merge
- [x] Put on/off
- [x] Apply base stats
- [x] Trash
- [x] Use
- [x] Trigrams

###### Monster
- [x] Idle
- [x] Chase
- [x] Walk
- [x] Old AI
- [ ] New AI
- [ ] Other AIs
- [x] Appear disappear in sight
- [x] Die
- [ ] Aggro with hostility
- [ ] Item drop
- [ ] EXP distrubution
- [x] Attack
- [ ] Final stats calculation

###### Spawner
- [ ] Load from GenMonster
- [ ] Keep track of monster lifetime
- [ ] Spawn

###### NPC
- [x] Load from InitNPC
- [x] Serve HTML from e.pk
- [x] Appear disappear in sight

###### Map
- [x] Cut map into smaller tiles
- [x] Search objects in certain distance
- [ ] Safezones

###### Socket
- [x] Receive
- [x] Send

###### Database Server
- [x] Connection pooling
