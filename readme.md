# Sonic 1 C Port

This is a work-in-progress full port of Sonic the Hedgehog for the Mega Drive (revision 1) to C.

What's ported:
- All "core" game code (graphics management, collision handling (object/level and object/object), level-specific code)
- All game objects, including the entire Sonic object

What's not ported:
- Horizontal blank handling (the water in Labyrinth Zone displays wrong)
- The sound driver (not the focus of the project; digital music support will be added later, other audio playback methods will be considered eventually)

A REV01 ROM of the original game is required, for reading data from it. Place it in the same folder as the executable and name it `s1built.bin`.

I accomplished this by writing a [program](./asmconverter) that generates "nearly-correct" C code from all the code it can find in the original ROM, assisted by a symbol map from [a disassembly](https://github.com/sonicretro/s1disasm) and a few heuristics. Then, I go through all the generated code and manually fix any issues from the generator that would be too complex to fix automatically (dynamic jumps, complex control flow, code that wasn't picked up by the converter). I compile the resulting C with TCC (though other compilers will probably work), and load it through a [separate program](./sonic1) written in Rust.

The program acts as a specialized "frontend" for [`speedshoes`](./speedshoes), a minimal Mega Drive emulation framework I wrote for this project. Speedshoes is capable of running the original ROM, albeit with some slight runtime patching to accomodate for extra features. Notably, it can detect whenever 68k subroutines are called, and is able to intercept those calls with calls into C "scripts". For the sake of accuracy with the game, the C scripts hold their own copy, and after every hook, the state of the C side is compared with the emulator. Additionally, Speedshoes supports checking accuracy at the level of individual instructions, allowing one to recreate a perfect reimplementation of a Mega Drive game down to the CPU register, without interpreting a single byte of code in ROM.

I intend for this port to be a basis from which myself and others can create derivative works of the game, retaining faithfulness to the original gameplay while not having to work in the original's 68000 assembly language.

### Informal build instructions
(This folder is fresh from a reorganization to make it easier to maintain through version control. I'll rewrite this soon...)

To build the game DLL:
- Grab [a distribution of TCC](http://download.savannah.gnu.org/releases/tinycc) and put it at the repo root, such that the path to TCC is `<repo root>/tcc/tcc.exe`
- Enter the `sonic1c` folder and run `build_game.cmd`. (If you want faster code without any accuracy checking, run `build_game_release.cmd`).
- You'll end up with `sonic1.dll` and `sonic1.def` (Windows)/`libsonic1.so` (*nix) in the repo root.

To build Speedshoes and the game runner:
- [Install Rust](https://www.rust-lang.org/tools/install). If you already have Rust installed, make sure you're using the 2021 edition.
- Enter the repo root and `cargo build` for a debug build, or `cargo build --release` for a release build.
- Enter the `sonic1` folder and `cargo run` fo a debug build, or `cargo run --release` for a release build. Release builds expect the game DLL to be in the same folder as it, so copy the DLL over as well.
