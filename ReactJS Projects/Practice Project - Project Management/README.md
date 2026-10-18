# Project Management App

A task and project management tool built with **React 18** and styled with **Tailwind CSS**.

## What it does

- Displays a start screen prompting the user to create their first project
- Lets users create new projects with a title, description, and due date
- Shows a sidebar listing all created projects for quick navigation
- Allows selecting a project to view its details and associated tasks
- Supports adding tasks to a project and deleting them individually
- Supports deleting entire projects

## Key React concepts demonstrated

| Concept | Where used |
|---------|-----------|
| `useState` (complex state) | Single top-level state object holding all projects and tasks; updated immutably |
| State lifting | All state lives in `App.jsx` and flows down via props to `StartMenu`, `NewProject`, and `Project` |
| Refs (`useRef`) | Accessing modal dialog DOM node imperatively for open/close control |
| Conditional rendering | Switching between start screen, new project form, and project detail view |
| List rendering with `key` | Dynamic project sidebar and per-project task lists |
| Tailwind CSS | Utility-first styling with responsive layout, hover states, and custom colour accents |

## Tech stack

- React 18.2
- Tailwind CSS 3.3
- PostCSS / Autoprefixer
- Vite 4

## Running locally

```bash
cd code
npm install
npm run dev
```

Open `http://localhost:5173` in your browser.
