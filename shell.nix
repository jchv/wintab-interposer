let pkgs = import <nixpkgs> {};
in
pkgs.mkShell {
  name = "wintab-interposer";
  nativeBuildInputs = with pkgs; [
    pkgsCross.mingwW64.buildPackages.gcc
    pkgsCross.mingw32.buildPackages.gcc
  ];
}
