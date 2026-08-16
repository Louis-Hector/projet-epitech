#!/bin/bash

docker run -it --rm --env-file .env --name persona-n8n -p 5678:5678 -v ~/.n8n:/home/node/.n8n n8nio/n8n
