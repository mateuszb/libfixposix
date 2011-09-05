/*******************************************************************************/
/* Permission is hereby granted, free of charge, to any person or organization */
/* obtaining a copy of the software and accompanying documentation covered by  */
/* this license (the "Software") to use, reproduce, display, distribute,       */
/* execute, and transmit the Software, and to prepare derivative works of the  */
/* Software, and to permit third-parties to whom the Software is furnished to  */
/* do so, all subject to the following:                                        */
/*                                                                             */
/* The copyright notices in the Software and this entire statement, including  */
/* the above license grant, this restriction and the following disclaimer,     */
/* must be included in all copies of the Software, in whole or in part, and    */
/* all derivative works of the Software, unless such copies or derivative      */
/* works are solely in the form of machine-executable object code generated by */
/* a source language processor.                                                */
/*                                                                             */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR  */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,    */
/* FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT   */
/* SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE   */
/* FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE, */
/* ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER */
/* DEALINGS IN THE SOFTWARE.                                                   */
/*******************************************************************************/

#include <lfp/select.h>
#include <stddef.h>

#include "utils.h"

int lfp_select(int nfds, fd_set *readfds, fd_set *writefds,
               fd_set *exceptfds, const struct timespec *timeout)
{
#if defined(HAVE_PSELECT)
    return pselect(nfds, readfds, writefds, exceptfds, timeout, NULL);
#else
    struct timeval tv;
    _lfp_timespec_to_timeval(timeout, &tv);
    return select(nfds, readfds, writefds, exceptfds, timeout);
#endif
}

void lfp_fd_clr(int fd, fd_set *set)
{
    FD_CLR(fd, set);
}

bool lfp_fd_isset(int fd, fd_set *set)
{
    return (bool) FD_ISSET(fd, set);
}

void lfp_fd_set(int fd, fd_set *set)
{
    FD_SET(fd, set);
}

void lfp_fd_zero(fd_set *set)
{
    FD_ZERO(set);
}
