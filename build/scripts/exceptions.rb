#!/usr/bin/env ruby
#
# Build OpenSSL libraries to use it to build Crystax NDK utilities
#
# Copyright (c) 2015 CrystaX .NET.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are
# met:
#
#    1. Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#
#    2. Redistributions in binary form must reproduce the above
#       copyright notice, this list of conditions and the following
#       disclaimer in the documentation and/or other materials provided
#       with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY CrystaX .NET ''AS IS'' AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL CrystaX .NET OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
# BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
# OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
# IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# The views and conclusions contained in the software and documentation
# are those of the authors and should not be interpreted as representing
# official policies, either expressed or implied, of CrystaX .NET.
#


class CommandFailed < RuntimeError
  def initialize(cmd, exitstatus)
    @cmd = cmd
    @exitstatus = exitstatus
  end

  def to_s
    "command failed:  #{@cmd}\n"
    "   exit status:  #{@exitstatus}\n"
  end
end


class UnknownTargetPlatform < RuntimeError
  def initialize(platform)
    @platform = platform
  end

  def to_s
    "unknown target platform #{@platform}"
  end
end


class UnknownTargetOS < RuntimeError
  def initialize(os)
    @os = os
  end

  def to_s
    "unknown target OS #{@os}"
  end
end
