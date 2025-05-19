/*


clear && make && valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell




test de mon lien git sur mon pc fixe


ihdghuigd rgdhui hui rgdzhui rgdho rgzphio srgeho srg         jh sgjosgd fgd


s Fgdrg g drg dthsthxfth

('"'") <- SEGFAULT

""""

"""

""""'

"ghchc""jhhv"jhk'khgyj'





ls>out |cat -e | rev | grep "$"<in|rev|cat|ls | a | ls<truc >> apend << heredoc | plein de trucs avec des espaces en + "couc ou  "             tab     |dw>d< sd


ls>out |cat -e | rev | grep "$" <in|rev|cat|ls | a | ls<truc >> apend << heredoc | plein de trucs avec des espaces en + "couc ou  "              tab |dw>d< sd


ls<truc >> apend << heredoc



*/






/*

19/05/2025

ls

lsl

exit -> ne sort pas du programme mais va dans l'exec necessite un deuxieme exit pour sortir




*/


/**/


/**/


/**/

/**/


/**/


/**/


/**/


/**/

/**/


/*

19/05/2025


💾 minishell :<infile echo bonjour
==489955== Invalid read of size 1
==489955==    at 0x402184: count_words (utils.c:48)
==489955==    by 0x4031E4: fill_s_k_tab (fill_suprem_knowledge.c:178)
==489955==    by 0x4041EC: fill_tabs (gluttony.c:17)
==489955==    by 0x40342A: fill_suprem_knowledge (fill_suprem_knowledge.c:246)
==489955==    by 0x4013AA: handle_str (main.c:171)
==489955==    by 0x401477: handle_readline (main.c:216)
==489955==    by 0x4017BA: main (main.c:343)
==489955==  Address 0x4bd9c2f is 1 bytes before a block of size 21 alloc'd
==489955==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==489955==    by 0x48AFBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==489955==    by 0x488D694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==489955==    by 0x4897D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==489955==    by 0x4016BA: main (main.c:318)
==489955==
==489955== Invalid read of size 1
==489955==    at 0x404BC4: glt_count_words (gluttony.c:148)
==489955==    by 0x404234: fill_gluttony_tab (gluttony.c:236)
==489955==    by 0x4041F9: fill_tabs (gluttony.c:18)
==489955==    by 0x40342A: fill_suprem_knowledge (fill_suprem_knowledge.c:246)
==489955==    by 0x4013AA: handle_str (main.c:171)
==489955==    by 0x401477: handle_readline (main.c:216)
==489955==    by 0x4017BA: main (main.c:343)
==489955==  Address 0x4bd9c2f is 1 bytes before a block of size 21 alloc'd
==489955==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==489955==    by 0x48AFBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==489955==    by 0x488D694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==489955==    by 0x4897D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==489955==    by 0x4016BA: main (main.c:318)
==489955==
HALLO



passage par handle_exec


bonjour


*/


/*

19/05/2025


problemes espace vide et TAB vide dans des guillemets aussi simple et double

plein de truc a tester avec du vide




*/


/*

19/05/2025


💾 minishell :"echo""bonjour"
passage par handle_exec


test
tmp :/home/qumiraud/.nix-profile/bin/
 /home/qumiraud/.nix-profile/bin/ <---tmp | /home/qumiraud/.nix-profile/bin/echobonjour <---find
test
tmp :/nix/var/nix/profiles/default/bin/
 /nix/var/nix/profiles/default/bin/ <---tmp | /nix/var/nix/profiles/default/bin/echobonjour <---find
test
tmp :/home/qumiraud/bin/
 /home/qumiraud/bin/ <---tmp | /home/qumiraud/bin/echobonjour <---find
test
tmp :/home/qumiraud/.nix-profile/bin/
 /home/qumiraud/.nix-profile/bin/ <---tmp | /home/qumiraud/.nix-profile/bin/echobonjour <---find
test
tmp :/nix/var/nix/profiles/default/bin/
 /nix/var/nix/profiles/default/bin/ <---tmp | /nix/var/nix/profiles/default/bin/echobonjour <---find
test
tmp :/usr/local/sbin/
 /usr/local/sbin/ <---tmp | /usr/local/sbin/echobonjour <---find
test
tmp :/usr/local/bin/
 /usr/local/bin/ <---tmp | /usr/local/bin/echobonjour <---find
test
tmp :/usr/sbin/
 /usr/sbin/ <---tmp | /usr/sbin/echobonjour <---find
test
tmp :/usr/bin/
 /usr/bin/ <---tmp | /usr/bin/echobonjour <---find
test
tmp :/sbin/
 /sbin/ <---tmp | /sbin/echobonjour <---find
test
tmp :/bin/
 /bin/ <---tmp | /bin/echobonjour <---find
test
tmp :/usr/games/
 /usr/games/ <---tmp | /usr/games/echobonjour <---find
test
tmp :/usr/local/games/
 /usr/local/games/ <---tmp | /usr/local/games/echobonjour <---find
test
tmp :/snap/bin/
 /snap/bin/ <---tmp | /snap/bin/echobonjour <---find
==462478== Invalid read of size 1
==462478==    at 0x4066A4: ft_strlen (in /home/qumiraud/CommonCore/minishell_v0.7/minishell)
==462478==    by 0x4065FB: ft_strdup (in /home/qumiraud/CommonCore/minishell_v0.7/minishell)
==462478==    by 0x403C9B: ft_exec_nopipe (ft_exec.c:130)
==462478==    by 0x403D63: handle_exec (ft_exec.c:147)
==462478==    by 0x4013CD: handle_str (main.c:191)
==462478==    by 0x401477: handle_readline (main.c:216)
==462478==    by 0x4017BA: main (main.c:343)
==462478==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==462478==
==462478==
==462478== Process terminating with default action of signal 11 (SIGSEGV)
==462478==  Access not within mapped region at address 0x0
==462478==    at 0x4066A4: ft_strlen (in /home/qumiraud/CommonCore/minishell_v0.7/minishell)
==462478==    by 0x4065FB: ft_strdup (in /home/qumiraud/CommonCore/minishell_v0.7/minishell)
==462478==    by 0x403C9B: ft_exec_nopipe (ft_exec.c:130)
==462478==    by 0x403D63: handle_exec (ft_exec.c:147)
==462478==    by 0x4013CD: handle_str (main.c:191)
==462478==    by 0x401477: handle_readline (main.c:216)
==462478==    by 0x4017BA: main (main.c:343)
==462478==  If you believe this happened as a result of a stack
==462478==  overflow in your program's main thread (unlikely but
==462478==  possible), you can try to increase the size of the
==462478==  main thread stack using the --main-stacksize= flag.
==462478==  The main thread stack size used in this run was 8388608.
==462478==
==462478== HEAP SUMMARY:
==462478==     in use at exit: 229,565 bytes in 418 blocks
==462478==   total heap usage: 1,446 allocs, 1,028 frees, 448,079 bytes allocated
==462478==
==462478== LEAK SUMMARY:
==462478==    definitely lost: 0 bytes in 0 blocks
==462478==    indirectly lost: 0 bytes in 0 blocks
==462478==      possibly lost: 0 bytes in 0 blocks
==462478==    still reachable: 13,278 bytes in 78 blocks
==462478==         suppressed: 216,287 bytes in 340 blocks
==462478== Reachable blocks (those to which a pointer was found) are not shown.
==462478== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==462478==
==462478== For lists of detected and suppressed errors, rerun with: -s
==462478== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 3 from 3)



*/


/*

19/05/2025


!!!!!!!!!!!FALSE!!!!!!!!!!


💾 minishell :echo '$USER'
passage par handle_exec


qumiraud


!!!!!!!!!!!TRUE!!!!!!!!!!


qumiraud@2A3:~/CommonCore/minishell_v0.7$ echo '$USER'
$USER


les simples quotes '' ne donne pas la valeur d'env, donne la valeur literalle donc pas qumiraud mais $USER

*/



/*

19/05/2025

!!!!!!!!!!!FALSE!!!!!!!!!!

💾 minishell :echo "b onjou     r" "ca" "v""a"
passage par handle_exec


b onjou	r ca va

||||||||||||||||||||||||||||||||||||||||||||||||||

!!!!!!!!!!!TRUE!!!!!!!!!!

qumiraud@2A3:~/CommonCore/minishell_v0.7$ echo "b onjouv    r" "ca" "v""a"
b onjouv	r ca va


probleme venant du TAB qui n'est pas pris en compte par le printf de ft_echo

*/
















/*

make: Nothing to be done for 'all'.
==63995== Memcheck, a memory error detector
==63995== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==63995== Using Valgrind-3.18.1 and LibVEX; rerun with -h for copyright info
==63995== Command: ./minishell
==63995==
💾 minishell :awd ">" awd

glt_word : 3

1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
1_word : 0
2_word : 0
count_l : 3
1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
glutto_tab[0]: awd

glutto_tab[1]: ">"

glutto_tab[2]: awd

💾 minishell :awd ">>" awd

glt_word : 3

1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
1_word : 0
2_word : 0
count_l : 4
1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
glutto_tab[0]: awd

glutto_tab[1]: ">>"

glutto_tab[2]: awd

💾 minishell :awd ">>' awd
missing quote
💾 minishell :awd '>>' awd

glt_word : 3

1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
1_word : 0
2_word : 0
count_l : 4
1_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 3
glutto_tab[0]: awd

glutto_tab[1]: '>>'

glutto_tab[2]: awd

💾 minishell :exit

glt_word : 1

1_word : 0
2_word : 0
2_word : 0
2_word : 0
2_word : 0
count_l : 4
glutto_tab[0]: exit

exit
==63995==
==63995== HEAP SUMMARY:
==63995==     in use at exit: 208,880 bytes in 244 blocks
==63995==   total heap usage: 588 allocs, 344 frees, 233,627 bytes allocated
==63995==
==63995== 13 bytes in 1 blocks are definitely lost in loss record 7 of 76
==63995==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==63995==    by 0x48AFBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==63995==    by 0x488D694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==63995==    by 0x4897D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==63995==    by 0x4014AD: main (main.c:133)
==63995==
==63995== LEAK SUMMARY:
==63995==    definitely lost: 13 bytes in 1 blocks
==63995==    indirectly lost: 0 bytes in 0 blocks
==63995==      possibly lost: 0 bytes in 0 blocks
==63995==    still reachable: 208,867 bytes in 243 blocks
==63995==         suppressed: 0 bytes in 0 blocks
==63995== Reachable blocks (those to which a pointer was found) are not shown.
==63995== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==63995==
==63995== For lists of detected and suppressed errors, rerun with: -s
==63995== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)



*/

/*


==292635==
==292635== HEAP SUMMARY:
==292635==     in use at exit: 208,558 bytes in 232 blocks
==292635==   total heap usage: 813 allocs, 581 frees, 254,140 bytes allocated
==292635==
==292635== 5 bytes in 1 blocks are definitely lost in loss record 1 of 70
==292635==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==292635==    by 0x405A60: ft_calloc (in /home/pjurdana/Desktop/Tronc commun/minishell_pl/minishell)
==292635==    by 0x40534C: ft_strdup (in /home/pjurdana/Desktop/Tronc commun/minishell_pl/minishell)
==292635==    by 0x405069: parse_cmd (tokens_to_list.c:96)
==292635==    by 0x401369: handle_str (main.c:92)
==292635==    by 0x401447: handle_readline (main.c:129)
==292635==    by 0x401750: main (main.c:250)
==292635==
==292635== LEAK SUMMARY:
==292635==    definitely lost: 5 bytes in 1 blocks
==292635==    indirectly lost: 0 bytes in 0 blocks
==292635==      possibly lost: 0 bytes in 0 blocks
==292635==    still reachable: 0 bytes in 0 blocks
==292635==         suppressed: 208,553 bytes in 231 blocks
==292635==
==292635== For lists of detected and suppressed errors, rerun with: -s


*/


/*

💾 minishell :ech bonjour
passage par handle_exec


test
tmp :/home/qumiraud/.nix-profile/bin/
 /home/qumiraud/.nix-profile/bin/ <---tmp | /home/qumiraud/.nix-profile/bin/ech <---find
test
tmp :/nix/var/nix/profiles/default/bin/
 /nix/var/nix/profiles/default/bin/ <---tmp | /nix/var/nix/profiles/default/bin/ech <---find
test
tmp :/home/qumiraud/bin/
 /home/qumiraud/bin/ <---tmp | /home/qumiraud/bin/ech <---find
test
tmp :/home/qumiraud/.nix-profile/bin/
 /home/qumiraud/.nix-profile/bin/ <---tmp | /home/qumiraud/.nix-profile/bin/ech <---find
test
tmp :/nix/var/nix/profiles/default/bin/
 /nix/var/nix/profiles/default/bin/ <---tmp | /nix/var/nix/profiles/default/bin/ech <---find
test
tmp :/usr/local/sbin/
 /usr/local/sbin/ <---tmp | /usr/local/sbin/ech <---find
test
tmp :/usr/local/bin/
 /usr/local/bin/ <---tmp | /usr/local/bin/ech <---find
test
tmp :/usr/sbin/
 /usr/sbin/ <---tmp | /usr/sbin/ech <---find
test
tmp :/usr/bin/
 /usr/bin/ <---tmp | /usr/bin/ech <---find
test
tmp :/sbin/
 /sbin/ <---tmp | /sbin/ech <---find
test
tmp :/bin/
 /bin/ <---tmp | /bin/ech <---find
test
tmp :/usr/games/
 /usr/games/ <---tmp | /usr/games/ech <---find
test
tmp :/usr/local/games/
 /usr/local/games/ <---tmp | /usr/local/games/ech <---find
test
tmp :/snap/bin/
 /snap/bin/ <---tmp | /snap/bin/ech <---find
==451614== Invalid read of size 1
==451614==    at 0x4066A4: ft_strlen (in /home/qumiraud/CommonCore/minishell_v0.7/minishell)
==451614==    by 0x4065FB: ft_strdup (in /home/qumiraud/CommonCore/minishell_v0.7/minishell)
==451614==    by 0x403C9B: ft_exec_nopipe (ft_exec.c:130)
==451614==    by 0x403D63: handle_exec (ft_exec.c:147)
==451614==    by 0x4013CD: handle_str (main.c:191)
==451614==    by 0x401477: handle_readline (main.c:216)
==451614==    by 0x4017BA: main (main.c:343)
==451614==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==451614==
==451614==
==451614== Process terminating with default action of signal 11 (SIGSEGV)
==451614==  Access not within mapped region at address 0x0
==451614==    at 0x4066A4: ft_strlen (in /home/qumiraud/CommonCore/minishell_v0.7/minishell)
==451614==    by 0x4065FB: ft_strdup (in /home/qumiraud/CommonCore/minishell_v0.7/minishell)
==451614==    by 0x403C9B: ft_exec_nopipe (ft_exec.c:130)
==451614==    by 0x403D63: handle_exec (ft_exec.c:147)
==451614==    by 0x4013CD: handle_str (main.c:191)
==451614==    by 0x401477: handle_readline (main.c:216)
==451614==    by 0x4017BA: main (main.c:343)
==451614==  If you believe this happened as a result of a stack
==451614==  overflow in your program's main thread (unlikely but
==451614==  possible), you can try to increase the size of the
==451614==  main thread stack using the --main-stacksize= flag.
==451614==  The main thread stack size used in this run was 8388608.
==451614==
==451614== HEAP SUMMARY:
==451614==     in use at exit: 227,722 bytes in 335 blocks
==451614==   total heap usage: 578 allocs, 243 frees, 251,489 bytes allocated
==451614==
==451614== LEAK SUMMARY:
==451614==    definitely lost: 0 bytes in 0 blocks
==451614==    indirectly lost: 0 bytes in 0 blocks
==451614==      possibly lost: 0 bytes in 0 blocks
==451614==    still reachable: 13,286 bytes in 81 blocks
==451614==         suppressed: 214,436 bytes in 254 blocks
==451614== Reachable blocks (those to which a pointer was found) are not shown.
==451614== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==451614==
==451614== For lists of detected and suppressed errors, rerun with: -s
==451614== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
💾 minishell :


*/
