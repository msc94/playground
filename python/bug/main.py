import tempfile
import httpx
import asyncio

file = tempfile.SpooledTemporaryFile(mode="rw")
file.write("Hello World")

async def main():
    async with httpx.AsyncClient() as client:
        await client.put("http://localhost:9998/meta", data=file)

asyncio.run(main())