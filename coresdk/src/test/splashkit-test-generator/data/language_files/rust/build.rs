use std::env;
use std::path::PathBuf;

fn main() {
    let manifest_dir = PathBuf::from(env::var("CARGO_MANIFEST_DIR").unwrap_or_else(|_| String::from("/")));

    let lib_path = manifest_dir
        .parent()
        .unwrap()
        .join("cpp")
        .join("lib")
        .canonicalize()
        .expect("Failed to get absolute lib path");

    let search_path = match env::consts::OS {
        "macos" => lib_path.join("macos"),
        "linux" => lib_path.join("linux"),
        "windows" => lib_path.join("win64"),
        _ => panic!("Unsupported operating system")
    };

    println!("cargo:rustc-link-search=native={}", search_path.display());
    println!("cargo:rustc-link-lib=dylib=SplashKitBackend");
    println!("cargo:rerun-if-changed=build.rs");
}