#!/usr/bin/perl -w 
use strict;
use sigtrap;
use warnings;
use IO::Socket;
chomp(my $remoteStr = <STDIN>);
my ($remoteHost, $remotePort) = split /:/, $remoteStr;
chomp(my $nickname = <STDIN>);
chomp(my $username = <STDIN>);
chomp(my $realname = <STDIN>);
my $socket = IO::Socket::INET->new(
        PeerAddr => $remoteHost,
        PeerPort => $remotePort,
        Proto    => "tcp",
        Type     => SOCK_STREAM
        ) or die "Couldn't connect to $remoteHost:$remotePort : $@\n";
my $msg1 = "NICK $nickname\r\n";
my $msg2 = "USER $username 0 * :$realname\r\n";
print $socket $msg1;
print $socket $msg2;
while (<$socket>) {
    my ($str1,$str2) = split / /, $_;
    if ($str1 eq "PING") {
        print $socket "PONG $str2\r\n";
    }
    else {
        print "$_";
    }
}
