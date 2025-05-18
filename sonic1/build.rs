use std::path::{Path, PathBuf};
use std::{env, fs};

fn get_files_in_dir(
    dir: &Path,
    extension: &str,
    ret: Option<&mut Vec<String>>,
    exclusions: &[&str],
) -> Vec<String> {
    let mut binding = Vec::new();
    let ret = ret.unwrap_or(&mut binding);

    if dir.is_dir() {
        for entry in fs::read_dir(dir).unwrap() {
            let entry = entry.unwrap();
            let path = entry.path();
            if path.is_dir() {
                get_files_in_dir(&path, extension, Some(ret), exclusions);
            } else {
                if let Some(path_extension) = path.extension() {
                    let our_extension = if extension.starts_with('.') {
                        &extension[1..]
                    } else {
                        extension
                    };
                    if !exclusions.contains(&path.file_name().unwrap().to_str().unwrap())
                        && path_extension.to_str().unwrap() == our_extension
                    {
                        ret.push(String::from(path.to_str().unwrap()));
                    }
                }
            }
        }
    }

    ret.clone()
}

fn set_up_sdl2() {
    #[cfg(target_os = "macos")]
    println!("cargo:rustc-link-arg=-Wl,-rpath,@loader_path");

    #[cfg(target_os = "linux")]
    println!("cargo:rustc-link-arg=-Wl,-rpath,$ORIGIN");

    let target = env::var("TARGET").unwrap();
    if target.contains("pc-windows") {
        let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap());
        let mut lib_dir = manifest_dir.clone().parent().unwrap().to_path_buf();
        let mut dll_dir = manifest_dir.clone().parent().unwrap().to_path_buf();
        lib_dir.push("nativelibs");
        dll_dir.push("nativelibs");
        if target.contains("msvc") {
            lib_dir.push("msvc");
            dll_dir.push("msvc");
        } else {
            lib_dir.push("gnu-mingw");
            dll_dir.push("gnu-mingw");
        }
        lib_dir.push("lib");
        dll_dir.push("dll");
        if target.contains("x86_64") {
            lib_dir.push("64");
            dll_dir.push("64");
        } else {
            lib_dir.push("32");
            dll_dir.push("32");
        }
        println!("cargo:rustc-link-search=all={}", lib_dir.display());
        for entry in std::fs::read_dir(dll_dir).expect("Can't read DLL dir") {
            let entry_path = entry.expect("Invalid fs entry").path();
            let file_name_result = entry_path.file_name();
            let mut new_file_path = manifest_dir.clone();
            if let Some(file_name) = file_name_result {
                let file_name = file_name.to_str().unwrap();
                if file_name.ends_with(".dll") {
                    new_file_path.push(file_name);
                    std::fs::copy(&entry_path, new_file_path.as_path())
                        .expect("Can't copy from DLL dir");
                }
            }
        }
    }
}

#[cfg(feature = "static-game")]
fn static_game() {
    println!("cargo::rerun-if-changed=../sonic1c");
    cc::Build::new()
        .files(&get_files_in_dir(Path::new("../sonic1c"), ".c", None, &[]))
        .compile("sonic1c");
}

fn main() -> Result<(), String> {
    set_up_sdl2();
    #[cfg(feature = "static-game")]
    static_game();
    Ok(())
}
