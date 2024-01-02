# Dobbie The House Elf

Your name is Dobbie, you are a house elf with the goal to break your dear friend Harry Podder from the wicked clutches of the Dursliey Family. Your goal is to find the fastest route to Hogwards, while avoiding the Malvoy Mansion and the eerie Mr. Malvoy. Unfortunately for you, as all things in this modern word, it costs coin to enter a residence, while you and your friend Harry only have a collective 250 coin (don't worry, you bring no coin to the table in this partnership).

Luckily for you, Dobbie comes standard with House Elf Tools and Powers, mainly:
 - Teleportation between known locations.
 - An ePhone with a GPS that shows all reachable locations from your current position and their respective cost for entering.
 - A brain that acts shockingly similar to the C programming language.

Find the cheapest path from the Durslieys, to Hogwards. If you enter a residence and find that you have fallen back in the clutches of the Durslieys, the Malvoys, or run out of coin, you are then trapped where you are and have failed to get Harry to Hogwards.

The format of the input file is henceforth:
coin location reachable_jumps

Example input file easyCoin.txt:
```
1 The Durslieys House 3
1 Albus Bumbledores Chamber 7
1 The Great Hall 2
1 The Night Bus 1
1 Nicholas Flamel Lane 3
1 Dr. James Plank Drive 8
1 The Order of The Pegasus 1
1 Dr. Katie Court 5
1 The Borrow 3
1 Wendys 5
1 Diagonal Lane 3
1 The Leaky Pot 2
1 Olivanders 4
1 The Chamber of Confidential Information 6
1 Your Room 10
1 Hogwartz Third Floor Corridor 4
1 Hagrids 6
1 The Malvoy Mansion 6
1 Hogwards 9
```

- coin: The amount of coin required to enter, this will be deducted from your coin upon entry 
- location: The location name, this may be many words
- reachable_jumps: The number of jumps you can reach from the given location

Your job is to write dobbie.c, returning the cheapest path from the Durslieys to Hogwards. Be sure to not fall back into the clutches of the Durslieys, nor the Malvoys. If you cannot reach Hogwards through any path without running out of coin, return the following error message:

```
Ran out of funds at: location
```

