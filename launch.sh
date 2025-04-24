#!/bin/bash
docker run --rm -it   --cap-add=NET_RAW   -v /Users/colinprojean/Documents/42/ft_ping:/workspace   -w /workspace   ft_ping
