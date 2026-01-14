# SMTP Agent

A lightweight SMTP client implemented in C that connects to a remote SMTP server, performs a full SMTP exchange, and sends the contents of a local file as an email message.

---

## Features

- Implements the SMTP protocol end-to-end
- Uses a persistent, stateful connection
- Sends email data from a file of arbitrary length
- Validates server responses after every command
- Gracefully terminates the SMTP session

---

## SMTP Flow

1. HELO
2. MAIL FROM
3. RCPT TO
4. DATA
5. Email body transmission
6. DATA termination (`<CRLF>.<CRLF>`)
7. QUIT

---

## Run

```bash
./sans smtp client <smtp-server> <port>
```

### Example

```bash
./sans smtp client lunar.open.sice.indiana.edu 25
```

---

## Input

```
user@example.com
email.txt
```

---

## Notes

- Each SMTP command is sent individually and validated via server responses
- The client appends a DATA termination sequence if not present in the file
- Designed to operate over a restricted SMTP server for safe testing

---

## Tech

- Language: C
- Networking via provided SANS socket interface
- File I/O for email body handling
