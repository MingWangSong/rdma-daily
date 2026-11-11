(() => {
  'use strict';
  const dialog = document.querySelector('.image-dialog');
  let opener;
  if (dialog && typeof dialog.showModal === 'function') {
    const close = () => dialog.close();
    document.querySelectorAll('[data-zoom]').forEach(link => {
      link.addEventListener('click', event => {
        if (event.metaKey || event.ctrlKey || event.shiftKey || event.altKey) return;
        event.preventDefault();
        opener = link;
        const figure = link.closest('figure');
        const img = dialog.querySelector('img');
        img.src = link.href;
        img.alt = link.querySelector('img').alt;
        dialog.querySelector('.dialog-title').textContent = figure.querySelector('.figure-name').textContent;
        dialog.querySelector('.dialog-caption').innerHTML = figure.querySelector('figcaption').innerHTML;
        dialog.showModal();
        document.body.classList.add('body-dialog-open');
      });
    });
    dialog.querySelector('.dialog-close').addEventListener('click', close);
    dialog.addEventListener('click', event => {
      const box = dialog.getBoundingClientRect();
      if (event.target === dialog && (event.clientX < box.left || event.clientX > box.right || event.clientY < box.top || event.clientY > box.bottom)) close();
    });
    dialog.addEventListener('close', () => {
      document.body.classList.remove('body-dialog-open');
      if (opener) opener.focus({preventScroll:true});
    });
  }
  if ('IntersectionObserver' in window) {
    const links = [...document.querySelectorAll('.nav-inner a[href^="#"]')];
    const observer = new IntersectionObserver(entries => {
      const visible = entries.filter(entry => entry.isIntersecting);
      if (!visible.length) return;
      const id = visible[0].target.id;
      links.forEach(link => {
        const active = link.getAttribute('href') === '#' + id;
        link.classList.toggle('active', active);
        if (active) link.setAttribute('aria-current', 'location');
        else link.removeAttribute('aria-current');
      });
    }, {rootMargin:'-8% 0px -77% 0px'});
    document.querySelectorAll('.paper[id]').forEach(paper => observer.observe(paper));
  }
})();
