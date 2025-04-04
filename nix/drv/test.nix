# derivation {
#   name = "my-program";
#   system = "aarch64-darwin";
#   builder = "/bin/bash";
#   src = ./main.c;
#   args = [ "-c" ''
#     /usr/bin/clang $src -o $out
#   ''];
# }

let pkgs = import <nixpkgs> {}; in
pkgs.stdenv.mkDerivation {
  name = "my-program";
  src = ./main.c;
  nativeBuildInputs = [ 
    pkgs.clang
  ];
  buildInputs = [
    
  ];
  dontUnpack = true;
  buildPhase = ''
    clang $src -o my-program
  '';
  installPhase = ''
    mkdir -p $out/bin
    cp my-program $out/bin
  '';
}
