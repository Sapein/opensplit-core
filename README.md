opensplit-core
==============
   opensplit-core is the core library for the OpenSplit program, and anyone else wanting to use OpenSplit functionality.


### Features
[TO BE WRITTEN]

### Requirements
1. livesplit-core

### Development Setup
[TO BE WRITTEN]

## QnA  
#### Why do you use livesplit-core?  
   Because it has certain things that are just easier to use atm, like support for several different file formats, and it also creates almost 100% drop-in support for most LiveSplit configurations.

### Why not just use livesplit-core?   
   Because it doesn't have some features that I need (like AutoSplitting). Further, I plan to move away from livesplit-core in the future.

#### Why not just contribute to livesplit-core?  
   Because it's written in Rust, and I don't know Rust. This entire library is written in C.

#### Why don't you contribute to livesplit-core?  
   Because I don't know Rust. I do know C, and I might, one day, rewrite this in Rust. However, until I do, I don't think you will see a merge or any combination of work between LiveSplit and OpenSplit.

#### Why do you use C?  
   Because I felt it was the best option when writing and creating this. I needed something performant, and this is really the closest thing I have. The other option I really had was Python 3.

#### Do you plan to eventually move entirely to livesplit-core?  
   Potentially, however I do eventually plan to move away from livesplit-core, and only really rely on it for comptability with LiveSplit.
