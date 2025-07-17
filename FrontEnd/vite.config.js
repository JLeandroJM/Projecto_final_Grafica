import { defineConfig } from "vite"
import vue from "@vitejs/plugin-vue"

export default defineConfig({
  plugins: [vue()],
  server: {
    port: 2303,
    allowedHosts: ['4394-132-251-3-200.ngrok-free.app'],

  },
})
