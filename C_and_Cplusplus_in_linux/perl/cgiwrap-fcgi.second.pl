#!/usr/bin/perl -w
use FCGI;
use Socket;
use FCGI::ProcManager;
sub shutdown { FCGI::CloseSocket($socket); exit; }
sub restart  { FCGI::CloseSocket($socket); &main; }
use sigtrap 'handler', \&shutdown, 'normal-signals';
use sigtrap 'handler', \&restart,  'HUP';
require 'syscall.ph';
use POSIX qw(setsid);

#&daemonize; we don't daemonize when running under runsv
#this keeps the program alive or something after exec'ing perl scripts
END()   { }
BEGIN() { }
{
    no warnings;
    *CORE::GLOBAL::exit = sub { die "fakeexit\nrc=" . shift() . "\n"; };
};
q{exit};
if ($@) {
    exit unless $@ =~ /^fakeexit/;
}
&main;

sub daemonize() {
    chdir '/' or die "Can't chdir to /: $!";
    defined( my $pid = fork ) or die "Can't fork: $!";
    exit if $pid;
    setsid() or die "Can't start a new session: $!";
    umask 0;
}

sub main {

    #$socket = FCGI::OpenSocket( "127.0.0.1:8999", 10 ); #use IP sockets
    #$socket = FCGI::OpenSocket( "/var/run/nginx/cgiwrap-dispatch.sock", 10 ); #use UNIX sockets - user running this script must have w access to the 'nginx'
 folder!!
    #foreach $item (keys %ENV) { delete $ENV{$item}; }

    $proc_manager = FCGI::ProcManager->new( {n_processes => 5} );
    $socket = FCGI::OpenSocket( "/var/run/nginx/cgiwrap-dispatch.sock", 10 ); #use UNIX sockets - user running this script must have w access to the 'nginx'
folder!!
    $request =
        FCGI::Request( \*STDIN, \*STDOUT, \*STDERR, \%req_params, $socket,
        &FCGI::FAIL_ACCEPT_ON_INTR );
    $proc_manager->pm_manage();
    if ($request) { request_loop() }
    FCGI::CloseSocket($socket);
}

sub request_loop {
    while ( $request->Accept() >= 0 ) {
        $proc_manager->pm_pre_dispatch();
"cgiwrap-fcgi.pl" [dos] 164L, 6275C
                            print STDERR $errbytes;
                        }
                        if ($!) {
                            $err = $!;
                            die $!;
                            vec( $rin, fileno(PARENT_ERR), 1 ) = 0
                                unless ( $err == EINTR or $err == EAGAIN );
                        }
                    }
                    if ($r2) {
                        while ( $bytes = read( CHILD_O, $s, 4096 ) ) {
                            print $s;
                        }
                        if ( !defined($bytes) ) {
                            $err = $!;
                            die $!;
                            vec( $rin, fileno(CHILD_O), 1 ) = 0
                                unless ( $err == EINTR or $err == EAGAIN );
                        }
                    }
                    last if ( $e1 || $e2 );
                }
                close CHILD_RD;
                close PARENT_ERR;
                waitpid( $pid, 0 );
            } else {
                foreach $key ( keys %req_params ) {
                    $ENV{$key} = $req_params{$key};
                }

                # cd to the script's local directory
                if ( $req_params{SCRIPT_FILENAME} =~ /^(.*)\/[^\/]+$/ ) {
                    chdir $1;
                }
                close(PARENT_WR);

                #close(PARENT_ERR);
                close(STDIN);
                close(STDERR);

                #fcntl(CHILD_RD, F_DUPFD, 0);
                syscall( &SYS_dup2, fileno(CHILD_RD),  0 );
                syscall( &SYS_dup2, fileno(CHILD_ERR), 2 );

                #open(STDIN, "<&CHILD_RD");
                exec( $req_params{SCRIPT_FILENAME} );
                die("exec failed");
            }
        } else {
            print("Content-type: text/plain\r\n\r\n");
            print "Error: No such CGI app - $req_params{SCRIPT_FILENAME} may not exist or is not executable by this process.\n";
        }
    }
}

