# shell.nix
{
  pkgs ? import <nixpkgs> { },
}:
pkgs.mkShell {
  buildInputs = [
    pkgs.libsForQt5.qt5.qtbase
    pkgs.libsForQt5.qt5.qttools
    pkgs.libsForQt5.qt5.qtwayland
    pkgs.bison
    pkgs.flex
  ];
}
