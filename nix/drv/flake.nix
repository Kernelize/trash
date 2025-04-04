{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    kvim.url = "github:HCHogan/kvim";
  };

  outputs = { self, nixpkgs }: 
  let
    system = "aarch64-darwin";
    pkgs = nixpkgs.legacyPackages.${system};
  in 
  {
    devShells.${system}.default =
      pkgs.mkShell {
        buildInputs = [
          pkgs.hello
          pkgs.vim
        ];

        shellHook = ''
          echo "Hello from ${system}!"
        '';
      };
    # packages.aarch64-darwin.hello = nixpkgs.legacyPackages.aarch64-darwin.hello;
    # packages.aarch64-darwin.default = self.packages.aarch64-darwin.hello;
  };
}
