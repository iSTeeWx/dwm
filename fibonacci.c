void
dwindle(Monitor *m)
{
	unsigned int i, n;
	int nx, ny, nw, nh;
	int og = 5, ig = 5;
	int nv, hrest = 0, wrest = 0, r = 1;
	Client *c;

	for (n = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next), n++);
	if (n == 0)
		return;

	nx = m->wx + og;
	ny = m->wy + og;
	nw = m->ww - 2 * og;
	nh = m->wh - 2 * og;

	for (i = 0, c = nexttiled(m->clients); c; c = nexttiled(c->next)) {
		if (r) {
			if ((i % 2 && (nh - ig) / 2 <= (bh + 2*c->bw))
			   || (!(i % 2) && (nw - ig) / 2 <= (bh + 2*c->bw))) {
				r = 0;
			}
			if (r && i < n - 1) {
				if (i % 2) {
					nv = (nh - ig) / 2;
					hrest = nh - 2*nv - ig;
					nh = nv;
				} else {
					nv = (nw - ig) / 2;
					wrest = nw - 2*nv - ig;
					nw = nv;
				}
			}

			if ((i % 4) == 0) {
                ny += nh + ig;
                nh += hrest;
			}
			else if ((i % 4) == 1) {
				nx += nw + ig;
				nw += wrest;
			}
			else if ((i % 4) == 2) {
				ny += nh + ig;
				nh += hrest;
				if (i < n - 1)
					nw += wrest;
			}
			else if ((i % 4) == 3) {
                nx += nw + ig;
                nw -= wrest;
			}
			if (i == 0)	{
				if (n != 1) {
					nw = (m->ww - ig - 2*og) - (m->ww - ig - 2*og) * (1 - m->mfact);
					wrest = 0;
				}
				ny = m->wy + og;
			}
			else if (i == 1)
				nw = m->ww - nw - ig - 2*og;
			i++;
		}

		resize(c, nx, ny, nw - (2*c->bw), nh - (2*c->bw), False);
	}
}

