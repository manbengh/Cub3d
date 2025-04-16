leak sur les textures

    ==19847== HEAP SUMMARY:
    ==19847==     in use at exit: 896 bytes in 8 blocks
    ==19847==   total heap usage: 1,521 allocs, 1,513 frees, 1,199,954 bytes allocated
    ==19847== 
    ==19847== 88 bytes in 1 blocks are still reachable in loss record 1 of 8
    ==19847==    at 0x484DA83: calloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
    ==19847==    by 0x4078BB: mlx_int_new_xshm_image (in /home/ahbey/repo/cub3D/cub3D)
    ==19847==    by 0x407BE2: mlx_new_image (in /home/ahbey/repo/cub3D/cub3D)
    ==19847==    by 0x4084B7: mlx_int_parse_xpm (in /home/ahbey/repo/cub3D/cub3D)
    ==19847==    by 0x4088F1: mlx_xpm_file_to_image (in /home/ahbey/repo/cub3D/cub3D)
    ==19847==    by 0x406E5B: make_img (texture.c:78)
    ==19847==    by 0x406F2F: init_text (texture.c:92)
    ==19847==    by 0x4063DE: init_game (init_game.c:113)
    ==19847==    by 0x4049C4: my_game (my_game.c:45)
    ==19847==    by 0x4028BE: main (main.c:77)


leak map non valide
        Error !
        Flood 3


                111111111111

                000N00000


                111111111111111111
                10000000000000000001
                10000000000000000001
                10000000000000000001
                10000000000000000001
                10000000011000000001
                10000000011000000001
                10000000000000000001
                10000000001000000001
                10000000010000000001
                10000000000000000001
                11111111111111111111

==22251== Invalid read of size 1
==22251==    at 0x4032C5: check_flood (map_check.c:83)
==22251==    by 0x4035FD: check_my_map (map_check.c:135)
==22251==    by 0x402637: check_map (main.c:35)
==22251==    by 0x4027AD: init_struct (main.c:60)
==22251==    by 0x402856: main (main.c:74)
==22251==  Address 0x4d4698f is 1 bytes before a block of size 11 alloc'd
==22251==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==22251==    by 0x409837: ft_strdup (in /home/ahbey/repo/cub3D/cub3D)
==22251==    by 0x403473: fill_my_map (map_check.c:106)
==22251==    by 0x4035DB: check_my_map (map_check.c:133)
==22251==    by 0x402637: check_map (main.c:35)
==22251==    by 0x4027AD: init_struct (main.c:60)
==22251==    by 0x402856: main (main.c:74)
==22251== 
Error !
Flood 3




fonctionne pas
        NO                      ./textures/wallNorth.xpm  

    fail car le nom de la texture = [                  ./textures/wallNorth.xpm  ]



    fail space/tab dans les couleurs
            211,211,     211 // doit fonctionner


espaces apres nom de textures ca fail

        [                 ./textures/wallWest.xpm      ] // doit fonctionner