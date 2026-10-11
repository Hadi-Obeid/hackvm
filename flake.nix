{
  description = "NAND2Tetris Project 2: VM emulator in C";

  inputs = {
    flake-utils.url = "github:numtide/flake-utils";
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
  };
  outputs = { self, nixpkgs, flake-utils }:
    flake-utils.lib.eachDefaultSystem (system:
      let
        pkgs = import nixpkgs { inherit system; };
        
      in {
        devShells.default = pkgs.mkShell {
          packages = [
            pkgs.gcc 
            pkgs.gnumake
            pkgs.unity-test
          ];
          buildInputs = [
            pkgs.gcc 
            pkgs.gnumake
            pkgs.unity-test
          ];

          shellHook = ''
            export UNITY_INCLUDE_DIR="${pkgs.unity-test}/include/unity"
            export UNITY_SRC_DIR="${pkgs.unity-test}/src/"
            echo "⚡ Unity testing environment loaded! ⚡"
            echo "Unity header location: $UNITY_INCLUDE_DIR"
          '';
        };
    });
}
