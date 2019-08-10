/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_real_path.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdufaud <mdufaud@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/30 22:47:41 by mdufaud           #+#    #+#             */
/*   Updated: 2016/07/01 17:03:46 by rcherik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>

#ifdef __linux__

#include <sys/types.h>
#include <unistd.h>

std::string	getRealPath(void)
{
	char		tmp[32];
	char		buf[1024];
	int			bytes;
	std::string	s;
	
	sprintf(tmp, "/proc/%d/exe", getpid());
	bytes = readlink(tmp, buf, 1024);
	bytes = bytes > 1023 ? 1203 : bytes;
	if (bytes >= 0)
		buf[bytes] = 0;
	s = std::string(buf);
	s.erase(s.begin() + s.find_last_of("/"), s.end());
	s += std::string("/");
	return (s);
}

# elif __APPLE__

# include <mach-o/dyld.h>

std::string	getRealPath(void)
{
	char		buf[1024];
	uint32_t	size;
	std::string	s;

	size = 1024;
	if (_NSGetExecutablePath(buf, &size) != 0)
		return ("");
	buf[size - 1] = 0;
	s = std::string(buf);
	s.erase(s.begin() + s.find_last_of("/"), s.end());
	s += std::string("/");
	return (s);
}
# elif _WIN32

# include <Windows.h>

std::string	getRealPath(void)
{
	wchar_t		buf[MAX_PATH];
	int			size;
	std::string	s;

	size = GetModuleFileName(NULL, buf, MAX_PATH);
	buf[size] = 0;
	s = std::string(buf);
	s.erase(s.begin() + s.find_last_of("/"), s.end());
	s += std::string("/");
	return (s);
}
#endif
