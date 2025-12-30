# EasyLogin

A PAM module that lets you log in with a shorter password for a few minutes instead of your full password.

## Why on Earth is this useful?

![xkcd](https://imgs.xkcd.com/comics/is_it_worth_the_time.png)

This probably falls in the "save 5 seconds 5-10x a day" category, so in theory I can spend up to 12-24 hours working on this.

Also because learning to work with PAM is fun.

## Installation

Download the repo and run `sudo make install`. This will copy `easylogin-cli` to `/usr/local/bin/` and copy `easylogin.so` to `/lib/x86_64-linux-gnu/security`. (If your system uses a different path for PAM modules, adjust the path accordingly.)

Then in `/etc/pam.d/gdm-password`, add `auth sufficient easylogin.so` near the top of the file. You probably want it at the top but under `pam_nologin.so` and `pam_succeed_if.so user != root quiet_success`. Note that which file to edit may vary depending on your desktop manager.

## Usage

Run `easylogin-cli set-password` to set a short password. Note that it's stored plaintext on disk, so don't use anything too important. (For speed purposes you should probably just randomly generate a sequence of 3-5 characters.)

Then, in your favorite desktop environment, add a keyboard shortcut that runs `easylogin-cli set-timestamp 60` (to allow login for up to 60 seconds, or another number that you prefer). I have mine bound to Super+K, so when I want to lock the screen and be able to log back in quickly I can just press Super+K,L.

## Security notes

You only get 1 attempt to correctly enter your password. However, most other security features are absent - mainly, the password is stored plaintext with no hashing or key stretching, and string comparisons can leak timing information. Those issues shouldn't be too relevant here as the intended threat model is online attacks on the desktop login screen only. Do not use this on SSH or other login systems!
