# TowerAttack

## Overview

This C++ program written as a semestral project for a C++ programming class implements a two-dimensional console 'tower attack' game. The game's concept is similar to that of a regular tower attack game, except the player's goal here is to strategically buy and deploy troops so that they can push through the computer's defense and destroy the its base.

## Features

- **Load custom maps and troop and tower definitions**: The game supports setting the game map and other constants and variables from files during runtime, or you can use predefined values.
- **Easy to expand**: The game supports easy expansion in terms of adding new troop and tower types with new functionalities.
- **Console animation**: The game runs in console and offers simple UI and graphic animations.

## Troop types
- **Ground troop**: a basic troop with no special skills
- **Shield troop**: a ground troop with a shield with a predefined number of charges which save the troop from taking damage
- **Flying troop**: a troop that can travel over walls

## Tower types
- **Sniper tower**: deals damage to a single troop closest to the tower
- **Fire tower**: deals damage to all troops in its proximity
- **Freeze tower**: freezes/slows down troops in its proximity

## Game description
The task of the player is to destroy the enemy base. Enemy base has a predefined amount of HP and the player can bring the base HP down by succesfully pushing troops through the map into the base. Every map consists of the base and troop spawns. The player starts the game with a limited number of coins for which he can purchase troops and deploy them to any of the available spawns. Every game consists of a predefined number of waves, where after every wave the player gains more coins and the enemy defense gets stronger. The player wins if he can destroy the enemy base before all the waves are depleted.

## Game AI
The ground troops travel from their given spawn to the base along the fastest ground route - they cannot travel through walls. The flying troops travel along the fastest air route, ignoring walls. The computer uses a basic hotspot heuristic for placing down towers where the goal is to place the towers as close to as many troop paths as possible. The towers can only replace walls and therefore cannot obscure the ground paths.

## Waves
At the beginning of every wave, the player can purchase troops for the coins he has collected. After he is done purchasing the troops, the wave starts and the player can choose spawns to deploy his troops at, individually for every troop. Then the troops attempt to get through the map from spawn to the enemy base without dying. The player is rewarded with coins for every troop that makes it to the enemy base. The wave ends when all troops die/make it to the base or when the base is destroyed.
![image](https://github.com/user-attachments/assets/b0039343-14db-46f5-ad26-5fc556fb69ee)

![image](https://github.com/user-attachments/assets/bff10d09-9211-4a5f-b6cd-0aafb01bce48)

![image](https://github.com/user-attachments/assets/fbe66491-c2f6-491b-b518-c9a65de8b443)

